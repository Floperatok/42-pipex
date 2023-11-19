/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:30:33 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/19 14:25:50 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getpath(char *command, char **env)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	tmp = ft_getenv(env, "PATH");
	paths = ft_split(tmp, ':');
	free(tmp);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab(paths), path);
		free(path);
	}
	return (ft_free_tab(paths), ft_strdup(command));
}

void	execution(char **cmd, char **env)
{
	char	*path;

	path = ft_getpath(cmd[0], env);
	if (!path || (path[0] != '.' && path[0] != '/'))
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free(path);
		ft_free_tab(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, env) == -1)
	{
		perror("pipex");
		free(path);
		ft_free_tab(cmd);
		exit(EXIT_FAILURE);
	}
	ft_free_tab(cmd);
	free(path);
}

void	redirect_process(int pid, int *pipe_fd, char *av, char **env)
{
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execution(ft_split(av, ' '), env);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	make_pipe(char *av, char **env)
{
	int		pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	redirect_process(pid, pipe_fd, av, env);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd_in;
	int	fd_out;

	i = -1;
	if (ac > 1 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		check_ac(ac, 1);
		ft_here_doc(av[2]);
		i++;
	}
	else
	{
		check_ac(ac, 0);
		fd_in = open_file(av[1], O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	fd_out = open_file(av[ac - 1], O_WRONLY);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	while (++i < ac - 4)
		make_pipe(av[i + 2], env);
	execution(ft_split(av[ac - 2], ' '), env);
	return (0);
}
