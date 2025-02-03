/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 01:22:36 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/03 12:12:21 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	check_cubfile(char *gamefile, t_mlx *config)
{
	int	fd;

	fd = check_file_path(gamefile);
	if (fd == -1)
		return (1);
	readfile_to_list(fd, config);
	if (switch_info_to_list(config) == -1 || check_cub_content(config) == -1)
	{
		garbage_collector(config);
		return (-1);
	}
	return (0);
}

void	set_position(int i, int j, t_player *player, char c)
{
	if (c == 'W')
		player->dir = PI;
	else if (c == 'E')
		player->dir = 0;
	else if (c == 'N')
		player->dir = PI / 2;
	else if (c == 'S')
		player->dir = 3 * PI / 2;
}

// void	direction_to_wall(t_player *player, char **map)
// {
// 	double	angle;
// 	int	wall;
// 	int	face;
// 	int	x0;
// 	int	y0;
// 	int	x1;
// 	int	y1;

// 	angle = player->dir;
// 	wall = 0;
// 	x0 = player->x;
// 	y0 = player->y;
// 	if (angle > 0 && angle < PI)
// 		face = 1;
// 	else
// 		face = -1;
// 	while (!wall)
// 	{
// 		y1 = (y0 - y0 % PX) - 1;
// 		x1 = x0 + (y0 - y1) / tan(angle);
// 		if (check_wall(map, x1, y1))
// 			wall = 1;
// 		else
// 		{
// 			y0 += PX * face;
// 			x0 += PX / tan(angle);
// 		}
// 	}
// }

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
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				set_position(i, j, player, map[i][j]);
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
	mlx->img = malloc(sizeof(t_img));
	mlx->new_img = malloc(sizeof(t_img));
	mlx->player = malloc(sizeof(t_player));
	mlx->player->rays = malloc(sizeof(int) * 1);
	mlx->player->rays[0] = 0;
	get_player(mlx->map, mlx->player);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH * PX, HEIGHT * PX, "Cub3d");
	mlx->img->img = NULL;
	mlx->img->img = mlx_new_image(mlx->mlx, WIDTH * PX, HEIGHT * PX);
	render_game(mlx);
}

void	update_dir(t_player *player, int keycode)
{
	if (keycode == LEFT)
		player->dir -= PI / 60;
	if (keycode == RIGHT)
		player->dir += PI / 60;
	if (player->dir < 0)
		player->dir += 2 * PI;
	if (player->dir > 2 * PI)
		player->dir -= 2 * PI;
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
	if (keycode == LEFT || keycode == RIGHT)
		update_dir(player, keycode);
	if (keycode == ESC)
		close_game(mlx);
	render_game(mlx);
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

int	main(int ac, char **av, char **env)
{
	t_mlx	mlx;

	mlx.mlx = NULL;
	mlx.win = NULL;
	if (env && !env[0])
		return (prblem("error!\n", "environement NULL", "    *__*\n"));
	init_gameconfig(&mlx);
	if (ac == 2 && av[1] && av[1][0] != '\0')
	{
		if (check_cubfile(av[1], &mlx) != 0)
			return (1);
		printf("WORK!\n");
		// hna ghatbda lcode ! mlx dyalna ntl3o raycast dyalna
	}
	else
		ft_putstr_fd("Error!\nParameter not valid\n", 2);
	init(&mlx);
	mlx_hook(mlx.win, 2, (1L << 0), key_press, &mlx);
	// mlx_loop_hook(mlx.mlx, render_game, &mlx);
	mlx_loop(mlx.mlx);
	close_game(&mlx);
	return (0);
}
