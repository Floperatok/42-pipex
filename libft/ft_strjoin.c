/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:55:22 by nsalles           #+#    #+#             */
/*   Updated: 2023/10/28 15:49:41 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	lens1;
	size_t	lens2;
	size_t	i;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	res = (char *) malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < lens1)
		res[i] = s1[i];
	i--;
	while (++i < lens1 + lens2)
		res[i] = s2[i - lens1];
	res[i] = '\0';
	return (res);
}
