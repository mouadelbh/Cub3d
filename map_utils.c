/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 01:32:36 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/03 13:01:09 by mel-bouh         ###   ########.fr       */
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
