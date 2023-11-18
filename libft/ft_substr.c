/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:24:56 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/17 19:59:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	size_res;
	size_t	i;

	size_res = ft_strlen(s) - start;
	if (size_res > len)
		size_res = len;
	if (start >= ft_strlen(s))
	{
		res = (char *) malloc(sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	res = (char *) malloc(sizeof(char) * size_res + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < size_res)
		res[i] = s[start + i];
	res[i] = '\0';
	return (res);
}
