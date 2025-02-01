/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:23:30 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/01/26 06:35:32 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	check_wall(char **map, double x, double y)
{
	int	i;
	int	j;

	i = y / PX;
	j = x / PX;
	if (map[i][j] == '1')
		return (0);
	return (1);
}

int	get_distance_to_wall(char **map, t_player *player, int dir_x, int dir_y)
{
	int	next_x;
	int	next_y;
	int	distance;

	distance = 0;
	while (distance < PLAYER_SPEED)
	{
		next_x = player->x + dir_x * (distance + 1);
		next_y = player->y + dir_y * (distance + 1);
		if (!check_wall(map, next_x, next_y))
			break ;
		distance += 1;
	}
	return (distance);
}

int	move_right(t_mlx *mlx)
{
	t_player	*player;
	int			next_x;

	player = mlx->player;
	player->x += PLAYER_PX / 2;
	next_x = get_distance_to_wall(mlx->map, player, 1, 0);
	player->x -= PLAYER_PX / 2;
	player->x += next_x;
	return (0);
}

int	move_left(t_mlx *mlx)
{
	t_player	*player;
	int			next_x;

	player = mlx->player;
	player->x -= PLAYER_PX / 2;
	next_x = get_distance_to_wall(mlx->map, player, -1, 0);
	player->x += PLAYER_PX / 2;
	player->x -= next_x;
	return (0);
}

int	move_up(t_mlx *mlx)
{
	t_player	*player;
	int			next_y;

	player = mlx->player;
	player->y -= PLAYER_PX / 2;
	next_y = get_distance_to_wall(mlx->map, player, 0, -1);
	player->y += PLAYER_PX / 2;
	player->y -= next_y;
	return (0);
}

int	move_down(t_mlx *mlx)
{
	t_player	*player;
	int			next_y;

	player = mlx->player;
	player->y += PLAYER_PX / 2;
	next_y = get_distance_to_wall(mlx->map, player, 0, 1);
	player->y -= PLAYER_PX / 2;
	player->y += next_y;
	return (0);
}
