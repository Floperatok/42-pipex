/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:43:13 by nsalles           #+#    #+#             */
/*   Updated: 2023/10/17 07:01:58 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*src;
	size_t	i;

	src = (char *) s;
	i = ft_strlen(src);
	while (src[i] != (unsigned char) c)
	{
		if (i <= 0)
			return (NULL);
		i--;
	}
	return (&src[i]);
}
