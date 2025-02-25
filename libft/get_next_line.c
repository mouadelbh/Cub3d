/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:36:54 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/25 18:06:10 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(char *s, size_t n)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = (char *)malloc(n + 1);
	while (s[i] && i < n)
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (s3);
}

char	*set_next_line(char *prev_line)
{
	char	*new_line;

	new_line = ft_strchr(prev_line, '\n');
	if (!new_line)
		return (ft_strdup(prev_line));
	return (ft_strndup(prev_line, new_line - prev_line + 1));
}

char	*set_prev_line(char *prev_line)
{
	char	*new_line;
	char	*new_prev_line;

	new_line = ft_strchr(prev_line, '\n');
	if (!new_line)
	{
		free(prev_line);
		return (NULL);
	}
	new_prev_line = ft_strdup(new_line + 1);
	free(prev_line);
	if (*new_prev_line)
		return (new_prev_line);
	free(new_prev_line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*prev_line;
	char		*next_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	prev_line = read_line(fd, prev_line);
	if (!prev_line)
		return (NULL);
	next_line = set_next_line(prev_line);
	prev_line = set_prev_line(prev_line);
	return (next_line);
}
