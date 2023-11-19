/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:30:47 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/19 01:20:45 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Free the char ** tab, tab must be null terminated
void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	open_manager(char *infile, char *outfile)
{
	int	fd_infile;
	int	fd_outfile;

	fd_infile = open(infile, O_RDONLY, 0666);
	if (fd_infile == -1)
	{
		ft_putstr_fd("pipex: no such file of directory: ", 2);
		ft_putendl_fd(infile, 2);
		exit(EXIT_FAILURE);
	}
	fd_outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd_outfile == -1)
	{
		close(fd_infile);
		ft_putstr_fd("pipex: no such file of directory: ", 2);
		ft_putendl_fd(outfile, 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	return (fd_outfile);
}

// Returns the value of the environement [env] variable [var]
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
			return (free_tab(paths), path);
		free(path);
	}
	return (free_tab(paths), ft_strdup(command));
}
