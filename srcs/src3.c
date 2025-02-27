/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/27 15:15:06 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dist_ply_wall(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->p_w_dist = ((double)r->map_x - p->pos_x
				+ (1 - (double)r->step_x) / 2) / r->ray_x;
	else
		r->p_w_dist = ((double)r->map_y - p->pos_y
				+ (1 - (double)r->step_y) / 2) / r->ray_y;
}

void	draw_up_down(t_draw *d, t_ray *r)
{
	d->wall_height = (int)(SCREEN_H / r->p_w_dist);
	d->draw_start = SCREEN_H / 2 - d->wall_height / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = SCREEN_H / 2 + d->wall_height / 2;
	if (d->draw_end >= SCREEN_H)
		d->draw_end = SCREEN_H - 1;
}

t_imge	*find_txt_dir(t_mlx *c)
{
	if (c->ray.side == 1)
	{
		if (c->ray.ray_y < 0)
			return (c->draw.txt_we);
		else
			return (c->draw.txt_ea);
	}
	else
	{
		if (c->ray.ray_x < 0)
			return (c->draw.txt_no);
		else
			return (c->draw.txt_so);
	}
	return (NULL);
}

void	l3bar_wall(t_mlx *c, t_imge *txt)
{
	if (c->ray.side == 0)
		c->draw.wall_x = c->player.pos_y + c->ray.p_w_dist * c->ray.ray_y;
	else
		c->draw.wall_x = c->player.pos_x + c->ray.p_w_dist * c->ray.ray_x;
	c->draw.wall_x -= floor(c->draw.wall_x);
	c->draw.txt_x = c->draw.wall_x * txt->width;
	if ((c->ray.side == 0 && c->ray.ray_x > 0)
		|| (c->ray.side == 1 && c->ray.ray_y < 0))
		c->draw.txt_x = txt->width - c->draw.txt_x - 1;
}

int	find_txt_pixel_color(t_imge *txt, int x, int y)
{
	int		*color;
	int		i;

	i = (y * txt->ll) / 4 + x;
	color = (int *)txt->addr;
	return (color[i]);
}
