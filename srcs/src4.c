/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/27 15:15:12 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_imge *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	find_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	*put_pixel_color_colm(t_mlx *c, t_imge *txt)
{
	double	scale;
	int		*tmp;
	int		i;
	double	y;

	tmp = (int *)malloc(sizeof(int) * c->draw.wall_height);
	if (!tmp)
		return (NULL);
	scale = 1.0 * txt->height / c->draw.wall_height;
	y = 0;
	if (c->draw.wall_height > SCREEN_H)
		y = (c->draw.wall_height - SCREEN_H) / 2;
	i = -1;
	while (++i < c->draw.wall_height)
	{
		tmp[i] = find_txt_pixel_color(txt, (int)c->draw.txt_x,
				(int)(y * scale));
		y++;
		if ((int)(y * scale) >= txt->height)
			break ;
	}
	return (tmp);
}

int	put_pixel_col(t_mlx *c, t_imge *txt, int x)
{
	int	*column;
	int	i;
	int	j;

	column = put_pixel_color_colm(c, txt);
	if (!column)
		return (prblem("Error!\n", "Malloc failed: put_pixel_col\n", ""));
	i = -1;
	while (++i < c->draw.draw_start)
		my_mlx_pixel_put(&c->img, x, i,
			find_color(c->draw.c[0], c->draw.c[1], c->draw.c[2]));
	j = 0;
	while (c->draw.draw_start < c->draw.draw_end)
		my_mlx_pixel_put(&c->img, x, c->draw.draw_start++, column[j++]);
	while (c->draw.draw_end < SCREEN_H)
		my_mlx_pixel_put(&c->img, x, c->draw.draw_end++,
			find_color(c->draw.f[0], c->draw.f[1], c->draw.f[2]));
	free(column);
	return (0);
}

void	loop_ray(t_mlx *config)
{
	int		x;
	t_imge	*txt;

	x = 0;
	while (x < SCREEN_W)
	{
		creat_ray(&config->ray, &config->player, x);
		ft_dda(&config->ray, config->map);
		dist_ply_wall(&config->ray, &config->player);
		draw_up_down(&config->draw, &config->ray);
		txt = find_txt_dir(config);
		l3bar_wall(config, txt);
		put_pixel_col(config, txt, x);
		x++;
	}
}
