/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 01:22:36 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/01/26 06:01:41 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	get_player(char **map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				player->x = (j * PX) + (PX / 2);
				player->y = (i * PX) + (PX / 2);
			}
			j++;
		}
		i++;
	}
}

void	init(t_mlx *mlx)
{
	mlx->map = get_map(open("map.cub", O_RDONLY));
	mlx->img = malloc(sizeof(t_img));
	mlx->new_img = malloc(sizeof(t_img));
	mlx->player = malloc(sizeof(t_player));
	get_player(mlx->map, mlx->player);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH * PX, HEIGHT * PX, "Cub3d");
	mlx->img->img = NULL;
	mlx->img->img = mlx_new_image(mlx->mlx, WIDTH * PX, HEIGHT * PX);
	render_game(mlx);
}

int	key_press(int keycode, t_mlx *mlx)
{
	t_player	*player;

	player = mlx->player;
	if (keycode == W)
		move_up(mlx);
	if (keycode == S)
		move_down(mlx);
	if (keycode == A)
		move_left(mlx);
	if (keycode == D)
		move_right(mlx);
	if (keycode == ESC)
		close_game(mlx);
	return (0);
}

void	close_game(t_mlx *mlx)
{
	free_arr((void **)mlx->map, HEIGHT);
	// if (mlx->img->img)
	// 	mlx_destroy_image(mlx->mlx, mlx->img->img);
	// if (mlx->new_img->img)
	// 	mlx_destroy_image(mlx->mlx, mlx->new_img->img);
	free(mlx->img);
	free(mlx->new_img);
	free(mlx->player);
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	exit(0);
}

int main()
{
	t_mlx	mlx;

	mlx.mlx = NULL;
	mlx.win = NULL;
	mlx.map = get_map(open("map.cub", O_RDONLY));
	init(&mlx);
	mlx_hook(mlx.win, 2, (1L << 0), key_press, &mlx);
	mlx_loop_hook(mlx.mlx, render_game, &mlx);
	mlx_loop(mlx.mlx);
	close_game(&mlx);
	return (0);
}
