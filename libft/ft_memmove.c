/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:36:50 by nsalles           #+#    #+#             */
/*   Updated: 2023/10/17 07:02:10 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdest;
	unsigned char	*ptrsrc;
	size_t			i;

	ptrdest = (unsigned char *) dest;
	ptrsrc = (unsigned char *) src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (ptrsrc < ptrdest && ptrsrc + n >= ptrdest)
	{
		while (i < n)
		{
			ptrdest[n - i - 1] = ptrsrc[n - i - 1];
			i++;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
