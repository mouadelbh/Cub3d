/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/27 16:44:20 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_imge	*load_img(void *mlx, char *path)
{
	t_imge	*img;

	if (!mlx)
		return (NULL);
	img = (t_imge *)malloc(sizeof(t_imge));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (img->img == NULL)
	{
		ft_putstr_fd("Error: mlx_xpm_file_to_image\n", 2);
		free(img);
		return (NULL);
	}
	return (img);
}

int	load_all_texture(t_mlx *config, t_draw *d)
{
	d->txt_no = load_img(config->mlx, config->no);
	if (!d->txt_no)
		return (prblem("load texture NO failed\n", "", ""));
	d->txt_so = load_img(config->mlx, config->so);
	if (!d->txt_so)
		return (prblem("load texture SO failed\n", "", ""));
	d->txt_we = load_img(config->mlx, config->we);
	if (!d->txt_we)
		return (prblem("load texture WE failed\n", "", ""));
	d->txt_ea = load_img(config->mlx, config->ea);
	if (!d->txt_ea)
		return (prblem("load texture EA failed\n", "", ""));
	d->txt_no->addr = mlx_get_data_addr(d->txt_no->img, &d->txt_no->bpp,
			&d->txt_no->ll, &d->txt_no->ed);
	d->txt_so->addr = mlx_get_data_addr(d->txt_so->img, &d->txt_so->bpp,
			&d->txt_so->ll, &d->txt_so->ed);
	d->txt_we->addr = mlx_get_data_addr(d->txt_we->img, &d->txt_we->bpp,
			&d->txt_we->ll, &d->txt_we->ed);
	d->txt_ea->addr = mlx_get_data_addr(d->txt_ea->img, &d->txt_ea->bpp,
			&d->txt_ea->ll, &d->txt_ea->ed);
	return (0);
}

void	ft_dda(t_ray *r, char **map)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map[r->map_x][r->map_y] == '1')
			r->hit = 1;
	}
}

void	update_side(t_ray *r, t_player *ply)
{
	if (r->ray_x < 0)
	{
		r->step_x = -1;
		r->side_x = (ply->pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - ply->pos_x) * r->delta_x;
	}
	if (r->ray_y < 0)
	{
		r->step_y = -1;
		r->side_y = (ply->pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - ply->pos_y) * r->delta_y;
	}
}

void	creat_ray(t_ray *r, t_player *ply, int x)
{
	r->map_x = (int)ply->pos_x;
	r->map_y = (int)ply->pos_y;
	ply->camera_x = 2 * x / (double)SCREEN_H - 1;
	r->ray_x = ply->dir_x + ply->plane_x * ply->camera_x;
	r->ray_y = ply->dir_y + ply->plane_y * ply->camera_x;
	if (r->ray_x == 0)
		r->delta_x = INFINITY;
	else
		r->delta_x = sqrt(1 + (r->ray_y * r->ray_y) / (r->ray_x * r->ray_x));
	if (r->ray_y == 0)
		r->delta_y = INFINITY;
	else
		r->delta_y = sqrt(1 + (r->ray_x * r->ray_x) / (r->ray_y * r->ray_y));
	update_side(r, ply);
}
