/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Drendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:49:55 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/01/26 06:20:39 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_player(t_player *player, t_img *img)
{
	int		x;
	int		y;
	char	*dst;

	y = player->y - PLAYER_PX / 2;
	while (y < player->y + PLAYER_PX / 2)
	{
		x = player->x - PLAYER_PX / 2;
		while (x < player->x + PLAYER_PX / 2)
		{
			dst = img->addr + (y * img->line + x * (img->bits / 8));
			*(unsigned int *)dst = PLAYER;
			x++;
		}
		y++;
	}
}

void	draw_block(t_img *img, int width, int height, int color)
{
	char	*dst;
	int		y;
	int		x;

	y = height * PX + 1;
	while (y < (height + 1) * PX - 1)
	{
		x = width * PX + 1;
		while (x < (width + 1) * PX - 1)
		{
			dst = img->addr + (y * img->line + x * (img->bits / 8));
			*(unsigned int *)dst = color;
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

int	render_game(t_mlx *mlx)
{
	t_img	*new_img;

	new_img = mlx->new_img;
	new_img->img = mlx_new_image(mlx->mlx, WIDTH * PX, HEIGHT * PX);
	new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bits, &new_img->line, &new_img->end);
	buffer_img(mlx->new_img, mlx->map);
	draw_player(mlx->player, mlx->new_img);
	if (mlx->img->img)
		mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx->img->img = new_img->img;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->new_img->img, 0, 0);
	return (0);
}
