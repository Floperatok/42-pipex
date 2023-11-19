/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:48:58 by nsalles           #+#    #+#             */
/*   Updated: 2023/11/19 12:11:31 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*ft_strjoin_leakfree(char *s1, char *s2)
{
	char	*res;
	size_t	lens1;
	size_t	lens2;
	size_t	i;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!res)
		return (free(s1), NULL);
	i = -1;
	while (s1 && ++i < lens1)
		res[i] = s1[i];
	i--;
	while (s2 && ++i < lens1 + lens2)
		res[i] = s2[i - lens1];
	res[i] = '\0';
	free(s1);
	return (res);
}

static char	*clean_stash(char *stash)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	res = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!res)
		return (NULL);
	j = 0;
	i++;
	while (stash[i])
		res[j++] = stash[i++];
	res[j] = '\0';
	free(stash);
	return (res);
}

static char	*extract_line(char *stash)
{
	char	*line;
	int		line_size;
	int		i;

	line_size = 0;
	while (stash[line_size] != '\n' && stash[line_size] != '\0')
		line_size++;
	if (stash[line_size] == '\0')
	{
		if (line_size == 0)
			return (NULL);
		return (ft_strdup(stash));
	}
	i = 0;
	line_size++;
	line = (char *)malloc(sizeof(char) * (line_size + 1));
	if (!line)
		return (NULL);
	while (i < line_size)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_file(int fd, char *stash)
{
	char	*buf;
	char	*nl_found;
	int		readed;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	readed = 1;
	nl_found = NULL;
	while (readed > 0 && nl_found == NULL)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
			return (free(buf), free(stash), NULL);
		buf[readed] = '\0';
		stash = ft_strjoin_leakfree(stash, buf);
		if (!stash)
			return (free(buf), NULL);
		nl_found = ft_strchr(buf, '\n');
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
