/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/26 22:46:24 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_hook(void *param)
{
	t_mlx	*game;

	game = (t_mlx *)param;
	garbage_collector(game);
	exit (0);
}

void	display(t_mlx *config, t_imge *img)
{
	loop_ray(config);
	mlx_put_image_to_window(config->mlx, config->win, img->img, 0, 0);
}

void	rotation_camera(int keysym, t_mlx *config, t_player *p)
{
	double	dir_ref;
	double	plane_ref;

	dir_ref = p->dir_x;
	plane_ref = p->plane_x;
	if (keysym == XK_Right)
	{
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = dir_ref * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y
			* sin(-ROT_SPEED);
		p->plane_y = plane_ref * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
		display(config, &config->img);
	}
	else if (keysym == XK_Left)
	{
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = dir_ref * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = plane_ref * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
		display(config, &config->img);
	}
}

void	move_player_ns(int keysym, t_mlx *config, t_player *p)
{
	if (keysym == XK_w)
	{
		p->mov_x = p->pos_x + (p->dir_x * MOV_SPEED);
		p->mov_y = p->pos_y + (p->dir_y * MOV_SPEED);
		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0')
			p->pos_x += p->dir_x * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0')
			p->pos_y += p->dir_y * MOV_SPEED;
	}
	else if (keysym == XK_s)
	{
		p->mov_x = p->pos_x - (p->dir_x * MOV_SPEED);
		p->mov_y = p->pos_y - (p->dir_y * MOV_SPEED);
		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0')
			p->pos_x -= p->dir_x * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0')
			p->pos_y -= p->dir_y * MOV_SPEED;
	}
}

void	move_player_we(int keysym, t_mlx *config, t_player *p)
{
	if (keysym == XK_a)
	{
		p->mov_x = p->pos_x - (p->dir_y * MOV_SPEED);
		p->mov_y = p->pos_y + (p->dir_x * MOV_SPEED);
		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0')
			p->pos_x -= p->dir_y * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0')
			p->pos_y += p->dir_x * MOV_SPEED;
	}
	else if (keysym == XK_d)
	{
		p->mov_x = (p->pos_x + (p->dir_y * MOV_SPEED));
		p->mov_y = (p->pos_y - (p->dir_x * MOV_SPEED));
		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0')
			p->pos_x += p->dir_y * MOV_SPEED;
		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0')
			p->pos_y -= p->dir_x * MOV_SPEED;
	}
}
