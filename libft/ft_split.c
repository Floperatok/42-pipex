/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:44:46 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/18 13:18:31 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	ft_quote(int *in_quote, char s)
{
	if (*in_quote == 0 && s == 39)
		*in_quote = 1;
	else if (*in_quote == 1 && s == 39)
		*in_quote = 0;
	return (*in_quote);
}

static int	count_words(char const *s, char c)
{
	int	counter;
	int	in_word;
	int	in_quote;

	counter = 0;
	in_word = 0;
	in_quote = 0;
	while (*s)
	{
		if (*s == 39)
			in_quote = ft_quote(&in_quote, *s);
		if (!in_quote)
		{
			if (*s == c)
				in_word = 0;
			else if (!in_word)
			{
				in_word = 1;
				counter++;
			}
		}
		s++;
	}
	return (counter);
}

static void	ft_free_split(char **tab, int i)
{
	while (i >= 0)
		free(tab[i--]);
	free(tab);
}

static char	*get_word(char const *s, char c)
{
	int		size;
	char	*word;

	size = 0;
	if (s[size] == 39)
	{
		size++;
		while (s[size] != 39 && s[size])
			size++;
		size++;
	}
	else
		while (s[size] != c && s[size])
			size++;
	if (size == 0)
		return (NULL);
	word = ft_substr(s, 0, size);
	if (!word)
		return (NULL);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	tab = (char **) ft_calloc(sizeof(char *), count_words(s, c) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
		{
			tab[i] = get_word(s, c);
			if (!tab[i])
				return (ft_free_split(tab, i), NULL);
			s += ft_strlen(tab[i++]);
		}
	}
	tab[i] = NULL;
	return (tab);
}
