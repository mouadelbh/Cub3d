/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Drendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:49:55 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/21 14:31:49 by mel-bouh         ###   ########.fr       */
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

void	draw_rays(t_player *player, t_mlx *mlx)
{
	int		x;
	int		y;
	double	angle;
	double	len;

	rays_length(player, mlx->map);
	angle = player->dir;
	x = player->x + cos(angle) * player->rays[0];
	y = player->y - sin(angle) * player->rays[0];
	draw_line(mlx->new_img, player->x, player->y, x, y);
}

void	draw_hits(t_img *img)
{
	int i, j;
	int size = 3; // Half-length of the cross arms

	i = 0;
	while (i < HEIGHT * PX)
	{
		j = 0;
		while (j < WIDTH * PX)
		{
			if (hits[i][j] == 1)
			{
				for (int k = -size; k <= size; k++)
				{
					if (i + k >= 0 && i + k < HEIGHT * PX)
						put_pixel(img, j, i + k, 0xFFFFFF); // Vertical line
					if (j + k >= 0 && j + k < WIDTH * PX)
						put_pixel(img, j + k, i, 0xFFFFFF); // Horizontal line
				}
				hits[i][j] = 0;
			}
			else if (hits[i][j] == 2)
			{
				for (int k = -size; k <= size; k++)
				{
					if (i + k >= 0 && i + k < HEIGHT * PX)
						put_pixel(img, j, i + k, 0x00FF00); // Vertical line
					if (j + k >= 0 && j + k < WIDTH * PX)
						put_pixel(img, j + k, i, 0x00FF00); // Horizontal line
				}
				hits[i][j] = 0;
			}
			j++;
		}
		i++;
	}
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
	draw_hits(mlx->new_img);
	mlx->img->img = new_img->img;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->new_img->img, 0, 0);
	return (0);
}
