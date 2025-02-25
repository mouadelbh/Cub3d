/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 01:32:36 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/01/24 07:48:23 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	free_arr(void **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_realloc(char **map, int size, int i)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		return (free_arr((void **)map, i), NULL);
	while (j < i)
	{
		tmp[j] = map[j];
		j++;
	}
	free(map);
	return (tmp);
}

char	**get_map(int fd)
{
	char	*line;
	int		size;
	int		i;
	char	**map;

	size = 5;
	if (fd < 0)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i == size - 1)
		{
			size *= 2;
			map = ft_realloc(map, size, i);
		}
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}
