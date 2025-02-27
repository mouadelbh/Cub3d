/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:57:13 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/27 20:37:01 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	mouse_hook(int x, int y, t_mlx *config)
{
	t_player	*p;
	int			center;
	static int	last;

	(void)y;
	p = &config->player;
	center = SCREEN_W / 2;
	(void)center;
	if (x < last)
	{
		p->m_left = 1;
		p->m_right = 0;
		last = x;
	}
	else if (x > last)
	{
		p->m_right = 1;
		p->r_left = 0;
		last = x;
	}
	return (0);
}

int	key_hook(int keysym, t_mlx *config)
{
	t_player	*p;

	p = &config->player;
	if (keysym == XK_Escape)
	{
		garbage_collector(config);
		exit(0);
	}
	if (keysym == XK_Left)
		p->r_left = 1;
	else if (keysym == XK_Right)
		p->r_right = 1;
	else if (keysym == XK_w)
		p->up = 1;
	else if (keysym == XK_s)
		p->down = 1;
	else if (keysym == XK_a)
		p->left = 1;
	else if (keysym == XK_d)
		p->right = 1;
	return (0);
}

int	key_release(int key, t_mlx *config)
{
	t_player	*player;

	player = &config->player;
	if (key == XK_w)
		player->up = 0;
	else if (key == XK_s)
		player->down = 0;
	else if (key == XK_a)
		player->left = 0;
	else if (key == XK_d)
		player->right = 0;
	else if (key == XK_Left)
		player->r_left = 0;
	else if (key == XK_Right)
		player->r_right = 0;
	return (0);
}
