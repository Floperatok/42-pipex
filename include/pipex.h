/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:53:09 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/18 19:23:04 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"

char	*ft_getenv(char **env, char *var);
char	*ft_getpath(char *command, char **env);
int		open_manager(char *infile, char *outfile);
void	free_tab(char **tab);

#endif