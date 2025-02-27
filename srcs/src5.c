/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/27 20:18:00 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_delta_u_d(t_mov *ctl1, t_player *p)
{
	ctl1->delta_x = 0.0;
	ctl1->delta_y = 0.0;
	if (p->up)
	{
		ctl1->delta_x = p->dir_x * MOV_SPEED;
		ctl1->delta_y = p->dir_y * MOV_SPEED;
	}
	else if (p->down)
	{
		ctl1->delta_x = -p->dir_x * MOV_SPEED;
		ctl1->delta_y = -p->dir_y * MOV_SPEED;
	}
	ctl1->new_x = p->pos_x + ctl1->delta_x;
	ctl1->new_y = p->pos_y + ctl1->delta_y;
}

void	max_min_cell(t_mov *ctl1, t_player *p, t_mlx *config)
{
	ctl1->cell_x = (int)p->pos_x;
	if (ctl1->delta_x > 0)
	{
		if (config->map[ctl1->cell_x + 1][(int)p->pos_y] == '1')
		{
			ctl1->allowed_max = ctl1->cell_x + 0.90;
			if (ctl1->new_x > ctl1->allowed_max)
				ctl1->new_x = ctl1->allowed_max;
		}
	}
	else if (ctl1->delta_x < 0)
	{
		if (config->map[ctl1->cell_x - 1][(int)p->pos_y] == '1')
		{
			ctl1->allowed_min = ctl1->cell_x + 0.10;
			if (ctl1->new_x < ctl1->allowed_min)
				ctl1->new_x = ctl1->allowed_min;
		}
	}
}

void	move_player_ns(t_mlx *config, t_player *p)
{
	t_mov	ctl;

	get_delta_u_d(&ctl, p);
	max_min_cell(&ctl, p, config);
	ctl.cell_y = (int)p->pos_y;
	if (ctl.delta_y > 0)
	{
		if (config->map[(int)p->pos_x][ctl.cell_y + 1] == '1')
		{
			ctl.allowed_max = ctl.cell_y + 0.90;
			if (ctl.new_y > ctl.allowed_max)
				ctl.new_y = ctl.allowed_max;
		}
	}
	else if (ctl.delta_y < 0)
	{
		if (config->map[(int)p->pos_x][ctl.cell_y - 1] == '1')
		{
			ctl.allowed_min = ctl.cell_y + 0.10;
			if (ctl.new_y < ctl.allowed_min)
				ctl.new_y = ctl.allowed_min;
		}
	}
	p->pos_x = ctl.new_x;
	p->pos_y = ctl.new_y;
}

void	get_delta_w_e(t_mov *ctl1, t_player *p)
{
	ctl1->delta_x = 0.0;
	ctl1->delta_y = 0.0;
	if (p->left)
	{
		ctl1->delta_x = -p->dir_y * MOV_SPEED;
		ctl1->delta_y = p->dir_x * MOV_SPEED;
	}
	else if (p->right)
	{
		ctl1->delta_x = p->dir_y * MOV_SPEED;
		ctl1->delta_y = -p->dir_x * MOV_SPEED;
	}
	ctl1->new_x = p->pos_x + ctl1->delta_x;
	ctl1->new_y = p->pos_y + ctl1->delta_y;
}

void	move_player_we(t_mlx *config, t_player *p)
{
	t_mov	ctl;

	get_delta_w_e(&ctl, p);
	max_min_cell(&ctl, p, config);
	ctl.cell_y = (int)p->pos_y;
	if (ctl.delta_y > 0 && config->map[(int)p->pos_x][ctl.cell_y + 1] == '1')
	{
		if (ctl.new_y > ctl.cell_y + 0.90)
			ctl.new_y = ctl.cell_y + 0.90;
	}
	else if (ctl.delta_y < 0 && config->map[(int)p->pos_x][ctl.cell_y
		- 1] == '1')
	{
		if (ctl.new_y < ctl.cell_y + 0.10)
			ctl.new_y = ctl.cell_y + 0.10;
	}
	p->pos_x = ctl.new_x;
	p->pos_y = ctl.new_y;
}
