/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:30:33 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/19 01:39:11 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execution(char **cmd, char **env)
{
	char	*path;

	path = ft_getpath(cmd[0], env);
	if (!path || (path[0] != '.' && path[0] != '/'))
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free(path);
		free_tab(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, env) == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		free(path);
		free_tab(cmd);
		exit(EXIT_FAILURE);
	}
	free_tab(cmd);
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
		return (perror("pipex"));
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
	int	fd_out;

	if (ac < 5)
		return (ft_putstr_fd("Pipex must have at least 5 arguments\n", 2), 1);
	fd_out = open_manager(av[1], av[ac - 1]);
	i = -1;
	while (++i < ac - 4)
		make_pipe(av[i + 2], env);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execution(ft_split(av[ac - 2], ' '), env);
	return (0);
}
