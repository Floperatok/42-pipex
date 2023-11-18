/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:30:33 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/18 13:13:39 by nsalles          ###   ########.fr       */
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
	exit(EXIT_SUCCESS);
}

void	child(int *p_fd, char **av, char **env)
{
	char	**cmd;
	int		fd;

	close(p_fd[0]);
	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no such file of directory: ", 2);
		ft_putendl_fd(av[1], 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	cmd = ft_split(av[2], ' ');
	execution(cmd, env);
}

void	parent(int *p_fd, char **av, char **env)
{
	char	**cmd;
	int		fd;

	close(p_fd[1]);
	fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no such file of directory: ", 2);
		ft_putendl_fd(av[4], 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	cmd = ft_split(av[3], ' ');
	execution(cmd, env);
}

int	main(int ac, char **av, char **env)
{
	int	pid;
	int	fd[2];

	if (ac != 5)
		return (ft_putstr_fd("Pipex must have exactly 4 arguments\n", 2), 1);
	if (pipe(fd) == -1)
		return (perror("Error "), 1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (perror("Error "), 1);
	}
	if (pid == 0)
		child(fd, av, env);
	else
		parent(fd, av, env);
}
