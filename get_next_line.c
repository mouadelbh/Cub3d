/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:04:31 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/01/24 07:48:05 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

size_t	ft_strlchr(char *buf)
{
	size_t	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] && buf[i] != '\n')
		i++;
	return (i);
}

char	*getrest(char *full)
{
	char	*tmp;

	if (!full)
		return (NULL);
	if (!ft_strchr(full, '\n'))
		return (free(full), NULL);
	tmp = ft_substr(full, ft_strlchr(full) + 1, ft_strlen(full));
	free(full);
	full = tmp;
	return (full);
}

char	*getline(char *full)
{
	char	*line;

	if (!full)
		return (NULL);
	line = ft_substr(full, 0, ft_strlchr(full) + 1);
	return (line);
}

char	*join(int fd, char *line)
{
	char	*tmp;
	ssize_t	rd;

	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	rd = 1;
	while (rd > 0 && !ft_strchr(tmp, '\n'))
	{
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd < 0)
			return (free(tmp), free(line), NULL);
		tmp[rd] = '\0';
		line = ft_strjoin(line, tmp);
	}
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	line = join(fd, line);
	if (!line || !line[0])
		return (free(line), NULL);
	result = getline(line);
	line = getrest(line);
	return (result);
}
