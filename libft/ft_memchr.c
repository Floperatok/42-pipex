/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:54:55 by nsalles           #+#    #+#             */
/*   Updated: 2023/10/17 07:02:11 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	size_t			i;

	i = 0;
	src = (unsigned char *) s;
	if (n <= 0)
		return (NULL);
	while (src[i] != (unsigned char) c)
	{
		if (i >= n - 1)
			return (NULL);
		i++;
	}
	return (&src[i]);
}
