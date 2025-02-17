/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Drendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:49:55 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/17 06:34:52 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_player(t_player *player, t_img *img)
{
	int	x;
	int	y;

	y = player->y - PLAYER_PX / 2;
	while (y < player->y + PLAYER_PX / 2)
	{
		x = player->x - PLAYER_PX / 2;
		while (x < player->x + PLAYER_PX / 2)
		{
			put_pixel(img, x, y, PLAYER);
			x++;
		}
		y++;
	}
	// draw_direction(player, img);
}

void	draw_block(t_img *img, int width, int height, int color)
{
	int	y;
	int	x;

	y = height * PX + 1;
	while (y < (height + 1) * PX - 1)
	{
		x = width * PX + 1;
		while (x < (width + 1) * PX - 1)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	buffer_img(t_img *img, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (map[i][j] == '1')
				draw_block(img, j, i, WALL);
			else
				draw_block(img, j, i, FLOOR);
			j++;
		}
		i++;
	}
}

int	pythagore(int x0, int y0, int x, int y)
{
	int	Dx;
	int	Dy;
	int	result;

	Dx = abs(x - x0);
	Dy = abs(y - y0);
	result = sqrt(pow(Dx, 2) + pow(Dy, 2));
	return (result);
}

int	distance_x(int x0, int y0, double angle)
{
	int	x;
	int	y;
	int	len;
	int	result;

	if (cos(angle) == 0)
		return (-1);
	len = PX - x0 % PX;
	if (cos(angle) < 0)
		len = -1 * (x0 % PX);
	x = x0 + len;
	y = tan(angle) * len + y0;
	result = pythagore(x0, y0, x, y);
	return (result);
}

int	distance_y(int x0, int y0, double angle)
{
	int	x;
	int	y;
	int	len;
	int	result;

	if (sin(angle) == 0)
		return (-1);
	len = PX - y0 % PX;
	if (sin(angle) < 0)
		len = -1 * (y0 % PX);
	y = y0 + len;
	x = len / tan(angle) + x0;
	result = pythagore(x0, y0, x, y);
	return (result);
}

int	hit_wall(t_player *player, char **map, double angle)
{
	int	x;
	int	y;
	int	x_margin;
	int	y_margin;

	x_margin = 1;
	y_margin = 1;
	if (cos(angle) < 0)
		x_margin = -1;
	if (sin(angle) < 0)
		y_margin = -1;
	x = (player->x + cos(angle) * player->rays[0]) + x_margin;
	y = (player->y + sin(angle) * player->rays[0]) + y_margin;
	if (map[y / PX][x / PX] == '1')
		return (1);
	return (0);
}

// int	distance_to_vertical(t_player *player, char **map, double angle)
// {
// }

// int	distance_to_horizontal(t_player *player, char **map, double angle)
// {
// }

void	rays_length(t_player *player, char **map)
{
	int		dx;
	int		dy;
	int		sumdx;
	int		sumdy;
	int		x0;
	int		y0;
	int		wall;
	double	angle;
	int	i = 0;

	sumdx = 0;
	sumdy = 0;
	angle = player->dir;
	x0 = player->x;
	y0 = player->y;
	wall = 0;
	dx = distance_x(x0, y0, angle);
	dy = distance_y(x0, y0, angle);
	if (dx < dy)
		player->rays[0] = dx;
	else
		player->rays[0] = dy;
}

void	draw_rays(t_player *player, t_mlx *mlx)
{
	int		x;
	int		y;
	double	angle;
	double	len;

	rays_length(player, mlx->map);
	angle = player->dir;
	x = player->x + cos(angle) * player->rays[0];
	y = player->y + sin(angle) * player->rays[0];
	draw_line(mlx->new_img, player->x, player->y, x, y);
}

int	render_game(t_mlx *mlx)
{
	t_img	*new_img;

	new_img = mlx->new_img;
	new_img->img = mlx_new_image(mlx->mlx, WIDTH * PX, HEIGHT * PX);
	new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bits, &new_img->line, &new_img->end);
	buffer_img(mlx->new_img, mlx->map);
	draw_player(mlx->player, mlx->new_img);
	draw_rays(mlx->player, mlx);
	if (mlx->img->img)
		mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx->img->img = new_img->img;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->new_img->img, 0, 0);
	return (0);
}
