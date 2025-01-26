/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:10:16 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/01/24 07:47:55 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

size_t	ft_strchr(char *buf, char c)
{
	size_t	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;

	i = 0;
	if (!dst && src && !dstsize)
		return (ft_strlen(src));
	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (dstsize == 0 || len_d >= dstsize)
		return (dstsize + len_s);
	while (src[i] && i < (dstsize - 1 - len_d))
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	length;
	size_t	i;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	i = 0;
	if (start > length)
		start = length;
	else if (len > (length - start))
		len = length - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	s = s + start;
	*(sub + len) = '\0';
	while (len-- && *s)
	{
		*(sub + i) = *(s + i);
		i++;
	}
	if (!*sub)
		return (free(sub), NULL);
	return (sub);
}

char	*ft_strjoin(char *line, char *buf)
{
	char	*join;

	if (!line && !buf)
		return (NULL);
	join = (char *)malloc(ft_strlen(line) + ft_strlen(buf) + 1);
	if (!join)
		return (NULL);
	join[0] = '\0';
	if (line)
		ft_strlcat(join, line, ft_strlen(line) + 1);
	if (buf)
		ft_strlcat(join, buf, ft_strlen(buf) + ft_strlen(line) + 1);
	if (!join[0])
		return (free(join), NULL);
	return (free(line), join);
}
