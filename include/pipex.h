/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:53:09 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/19 14:25:44 by nsalles          ###   ########.fr       */
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

void	check_ac(int ac, int is_here_doc);
char	*ft_getenv(char **env, char *var);
char	*ft_getpath(char *command, char **env);
int		open_file(char *file, int o_flag);
void	ft_here_doc(char *limiter);

#endif