/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:30:47 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/12 16:56:27 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *	Pipex error message management.
*/
void	check_ac(int ac, int is_here_doc)
{
	if (is_here_doc)
	{
		if (ac < 6)
		{
			ft_putstr_fd("pipex: There must be at least 6 argmuments ", 2);
			ft_putstr_fd("when using here_doc\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (ac < 5)
		{
			ft_putstr_fd("pipex: There must be at least 5 argmuments\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

/*
 *	Open the file with the flags 'o_flags' and returns the file descriptor.
*/
int	open_file(char *file, int o_flag)
{
	int	fd;

	if (o_flag == O_RDONLY)
		fd = open(file, O_RDONLY, 0666);
	else if (o_flag == O_WRONLY)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
	{
		ft_putstr_fd("open_file: other flags than O_RDONLY and O_WRONLY ", 2);
		ft_putstr_fd("aren't supported\n", 2);
		exit(EXIT_FAILURE);
	}
	if (fd == -1)
	{
		close(fd);
		ft_putstr_fd("pipex: no such file of directory: ", 2);
		ft_putendl_fd(file, 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/*
 *	Returns the value of the given environment variable.
*/
char	*ft_getenv(char **env, char *var)
{
	int		i;
	int		j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] == var[j])
			j++;
		if (var[j] == '\0')
			return (ft_substr(env[i], j + 1, ft_strlen(&env[i][j])));
	}
	return (NULL);
}

/*
 *	Read in the standars input until the limiter is found. Write the readed text
 *	in the given pipe.
*/
void	here_doc_reading(char *limiter, int *pipe_fd)
{
	char	*line;

	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && \
			ft_strlen(limiter) == ft_strlen(line) - 1)
		{
			get_next_line(-1);
			free(line);
			close(pipe_fd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
}

/*
 *	Create a pipe and open a here document to write in it.
*/
void	ft_here_doc(char *limiter)
{
	int	pid;
	int	pipe_fd[2];

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
	if (pid == 0)
		here_doc_reading(limiter, pipe_fd);
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		wait(NULL);
	}
}
