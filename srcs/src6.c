/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/27 20:13:58 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	esc_hook(void *param)
{
	t_mlx	*game;

	game = (t_mlx *)param;
	garbage_collector(game);
	exit(0);
}

void	display(t_mlx *config, t_imge *img)
{
	loop_ray(config);
	mlx_put_image_to_window(config->mlx, config->win, img->img, 0, 0);
}

void	rotation_camera(t_player *p)
{
	double	dir_ref;
	double	plane_ref;

	dir_ref = p->dir_x;
	plane_ref = p->plane_x;
	if (p->r_right || p->m_right)
	{
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = dir_ref * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y
			* sin(-ROT_SPEED);
		p->plane_y = plane_ref * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
	}
	else if (p->r_left || p->m_left)
	{
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = dir_ref * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = plane_ref * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
}
