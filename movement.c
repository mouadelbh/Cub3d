/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:23:30 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/22 15:30:53 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	check_wall(char **map, double x, double y)
{
	int	i;
	int	j;

	i = y / PX;
	j = x / PX;
	if (i < 0 || i >= HEIGHT || j < 0 || j >= WIDTH)
		return (-1);
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

int move_up(t_mlx *mlx)
{
	t_player	*player;
	int			move_x;
	int			move_y;

	player = mlx->player;
	move_x = (int)(cos(player->dir) * PLAYER_SPEED);
	move_y = (int)(-sin(player->dir) * PLAYER_SPEED);
	player->x += move_x;
	player->y += move_y;
	return 0;
}

int move_down(t_mlx *mlx)
{
	t_player	*player;
	int			move_x;
	int			move_y;

	player = mlx->player;
	move_x = (int)(-cos(player->dir) * PLAYER_SPEED);
	move_y = (int)(sin(player->dir) * PLAYER_SPEED);
	player->x += move_x;
	player->y += move_y;
	return 0;
}

int move_right(t_mlx *mlx) // Strafe right
{
	t_player	*player;
	int			move_x;
	int			move_y;

    player = mlx->player;
	move_x = (int)(sin(player->dir) * PLAYER_SPEED);
	move_y = (int)(cos(player->dir) * PLAYER_SPEED);
	player->x += move_x;
	player->y += move_y;
    return 0;
}

int move_left(t_mlx *mlx)
{
	t_player	*player;
	int			move_x;
	int			move_y;

	player = mlx->player;
	move_x = (int)(-sin(player->dir) * PLAYER_SPEED);
	move_y = (int)(-cos(player->dir) * PLAYER_SPEED);
	player->x += move_x;
	player->y += move_y;
	return (0);
}
