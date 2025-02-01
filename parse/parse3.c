/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/01 22:18:06 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	have_right_wall(char **map, int i, int j)
{
	while (map[i][j] && map[i][j] != '\n')
	{
		if (map[i][j] == ' ')
			return (0);
		if (map[i][j] == '1')
			return (1);
		j++;
	}
	return (0);
}

static int	have_left_wall(char **map, int i, int j)
{
	while (j >= 0)
	{
		if (map[i][j] == ' ')
			return (0);
		if (map[i][j] == '1')
			return (1);
		j--;
	}
	return (0);
}

static int	have_top_wall(char **map, int i, int j)
{
	while (i >= 0)
	{
		if (map[i][j] == ' ' || map[i][j] == '\n')
			return (0);
		if (map[i][j] == '1')
			return (1);
		i--;
	}
	return (0);
}

static int	have_bottom_wall(char **map, int i, int j, int size)
{
	while (i < size)
	{
		if (map[i][j] == ' ' || map[i][j] == '\n')
			return (0);
		if (map[i][j] == '1')
			return (1);
		i++;
	}
	return (0);
}

int	is_surrounded_by_walls(char **map, int size, int i, int j) 
{
	if (have_right_wall(map, i, j) && have_left_wall(map, i, j)
		&& have_top_wall(map, i, j) && have_bottom_wall(map, i, j, size))
		return (1);
	return (0);
}
