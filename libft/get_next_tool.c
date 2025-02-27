/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:36:54 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/25 17:58:11 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*handle_prev_line(char *prev_line, char *buff)
{
	char	*new_line;

	new_line = ft_strchr(prev_line, '\n');
	if (new_line)
	{
		free(buff);
		return (prev_line);
	}
	return (NULL);
}

char	*read_and_join(int fd, char *prev_line, char *buff)
{
	ssize_t	bytes_read;
	char	*new_line;

	bytes_read = read(fd, buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		prev_line = ft_strjoin1(prev_line, buff);
		new_line = ft_strchr(buff, '\n');
		if (new_line)
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (NULL);
	return (prev_line);
}

char	*read_line(int fd, char *prev_line)
{
	char	*buff;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (prev_line && handle_prev_line(prev_line, buff))
		return (prev_line);
	prev_line = read_and_join(fd, prev_line, buff);
	free(buff);
	return (prev_line);
}
