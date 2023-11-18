/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:33:41 by nsalles           #+#    #+#             */
/*   Updated: 2023/10/17 07:02:17 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int a)
{
	int	counter;

	if (a == 0)
		return (1);
	if (a > 0)
		counter = 0;
	while (a)
	{
		a /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		sign;
	int		i;

	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	i = ft_intlen(n) + sign;
	res = (char *) malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	res[i] = '\0';
	while (--i >= sign)
	{
		res[i] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		res[0] = '-';
	return (res);
}
