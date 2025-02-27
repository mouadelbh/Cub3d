/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/27 17:18:39 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	esc_hook(void *param)
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

void	rotation_camera(t_player *p)
{
	double	dir_ref;
	double	plane_ref;

	dir_ref = p->dir_x;
	plane_ref = p->plane_x;
	if (p->r_right)
	{
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = dir_ref * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y
			* sin(-ROT_SPEED);
		p->plane_y = plane_ref * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
	}
	else if (p->r_left)
	{
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = dir_ref * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = plane_ref * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
}

void move_player_ns(t_mlx *config, t_player *p)
{
	double delta_x = 0.0, delta_y = 0.0;

	// Determine intended movement for forward/backward.
	if (p->up)
	{
		delta_x = p->dir_x * MOV_SPEED;
		delta_y = p->dir_y * MOV_SPEED;
	}
	else if (p->down)
	{
		delta_x = -p->dir_x * MOV_SPEED;
		delta_y = -p->dir_y * MOV_SPEED;
	}
	double new_x = p->pos_x + delta_x;
	double new_y = p->pos_y + delta_y;
	int cell_x = (int)p->pos_x;
	if (delta_x > 0)
	{
		if (config->map[cell_x + 1][(int)p->pos_y] == '1')
		{
			double allowed_max = cell_x + 0.90;
			if (new_x > allowed_max)
				new_x = allowed_max;
		}
	}
	else if (delta_x < 0)
	{
		if (config->map[cell_x - 1][(int)p->pos_y] == '1')
		{
			double allowed_min = cell_x + 0.10;
			if (new_x < allowed_min)
				new_x = allowed_min;
		}
	}
	int cell_y = (int)p->pos_y; // current cell in y
	if (delta_y > 0)
	{
		if (config->map[(int)p->pos_x][cell_y + 1] == '1')
		{
			double allowed_max = cell_y + 0.90;
			if (new_y > allowed_max)
				new_y = allowed_max;
		}
	}
	else if (delta_y < 0)
	{
		if (config->map[(int)p->pos_x][cell_y - 1] == '1')
		{
			double allowed_min = cell_y + 0.10;
			if (new_y < allowed_min)
				new_y = allowed_min;
		}
	}

	// Finally update the player's position with the (possibly clamped) new positions.
	p->pos_x = new_x;
	p->pos_y = new_y;
}


void move_player_we(t_mlx *config, t_player *p)
{
	double delta_x = 0.0;
	double delta_y = 0.0;

	// Compute the intended strafe movement.
	if (p->left)
	{
		delta_x = -p->dir_y * MOV_SPEED;
		delta_y =  p->dir_x * MOV_SPEED;
	}
	else if (p->right)
	{
		delta_x =  p->dir_y * MOV_SPEED;
		delta_y = -p->dir_x * MOV_SPEED;
	}

	// --- Horizontal Movement ---
	// Predict new x position.
	double new_x = p->pos_x + delta_x;
	int current_cell_x = (int)p->pos_x;  // player's current cell on x

	// If moving right and there's a wall on the right, limit new_x.
	if (delta_x > 0 && config->map[current_cell_x + 1][(int)p->pos_y] == '1')
	{
		// Allow movement up to 0.90 within the current cell.
		if (new_x > current_cell_x + 0.90)
			new_x = current_cell_x + 0.90;
	}
	// If moving left and there's a wall on the left, limit new_x.
	else if (delta_x < 0 && config->map[current_cell_x - 1][(int)p->pos_y] == '1')
	{
		// Allow movement only down to 0.10 within the current cell.
		if (new_x < current_cell_x + 0.10)
			new_x = current_cell_x + 0.10;
	}
	// Apply horizontal movement.
	p->pos_x = new_x;

	// --- Vertical Movement ---
	// Predict new y position.
	double new_y = p->pos_y + delta_y;
	int current_cell_y = (int)p->pos_y;  // player's current cell on y

	// If moving down and there's a wall below, limit new_y.
	if (delta_y > 0 && config->map[(int)p->pos_x][current_cell_y + 1] == '1')
	{
		if (new_y > current_cell_y + 0.90)
			new_y = current_cell_y + 0.90;
	}
	// If moving up and there's a wall above, limit new_y.
	else if (delta_y < 0 && config->map[(int)p->pos_x][current_cell_y - 1] == '1')
	{
		if (new_y < current_cell_y + 0.10)
			new_y = current_cell_y + 0.10;
	}
	// Apply vertical movement.
	p->pos_y = new_y;
}

// void	move_player_ns(int keysym, t_mlx *config, t_player *p)
// {
	// if (keysym == XK_w)
	// {
	// 	p->mov_x = p->pos_x + (p->dir_x * MOV_SPEED);
	// 	p->mov_y = p->pos_y + (p->dir_y * MOV_SPEED);
	// 	if (config->map[(int)p->mov_x][(int)p->pos_y] == '0')
	// 		p->pos_x += p->dir_x * MOV_SPEED;
	// 	if (config->map[(int)p->pos_x][(int)p->mov_y] == '0')
	// 		p->pos_y += p->dir_y * MOV_SPEED;
	// }
	// else if (keysym == XK_s)
	// {
	// 	p->mov_x = p->pos_x - (p->dir_x * MOV_SPEED);
	// 	p->mov_y = p->pos_y - (p->dir_y * MOV_SPEED);
	// 	if (config->map[(int)p->mov_x][(int)p->pos_y] == '0')
	// 		p->pos_x -= p->dir_x * MOV_SPEED;
	// 	if (config->map[(int)p->pos_x][(int)p->mov_y] == '0')
	// 		p->pos_y -= p->dir_y * MOV_SPEED;
	// }
// }

// void	move_player_we(int keysym, t_mlx *config, t_player *p)
// {
// 	if (keysym == XK_a)
// 	{
// 		p->mov_x = p->pos_x - (p->dir_y * MOV_SPEED);
// 		p->mov_y = p->pos_y + (p->dir_x * MOV_SPEED);
// 		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0')
// 			p->pos_x -= p->dir_y * MOV_SPEED;
// 		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0')
// 			p->pos_y += p->dir_x * MOV_SPEED;
// 	}
// 	else if (keysym == XK_d)
// 	{
// 		p->mov_x = (p->pos_x + (p->dir_y * MOV_SPEED));
// 		p->mov_y = (p->pos_y - (p->dir_x * MOV_SPEED));
// 		if (config->map[(int)p->mov_x][(int)p->pos_y] == '0')
// 			p->pos_x += p->dir_y * MOV_SPEED;
// 		if (config->map[(int)p->pos_x][(int)p->mov_y] == '0')
// 			p->pos_y -= p->dir_x * MOV_SPEED;
// 	}
// }
