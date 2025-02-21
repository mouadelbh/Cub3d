/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Draycasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:17:34 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/21 15:35:33 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

int	distance_x(int x0, int y0, int *xi, int *yi, double angle)
{
	int		grid_x;
	int		dx;
	int		result;
	double	d;

	angle = normalize_angle(angle);
	if (fabs(cos(angle)) < EPSILON)
		return (INT_MAX);
	if (cos(angle) > 0)
			grid_x = x0 + PX - (x0 % PX);
	else
	{
		if (x0 % PX == 0)
			grid_x = x0 - PX;
		else
			grid_x = x0 - (x0 % PX);
	}
	dx = grid_x - x0;
	d = fabs((double)dx / cos(angle));
	result = (int)round(d);
	*xi = grid_x;
	*yi = y0 - (int)round(d * sin(angle));
	if (*xi < 0 || *xi >= WIDTH * PX ||
		*yi < 0 || *yi >= HEIGHT * PX)
		return (INT_MAX);
	return (result);
}

int	distance_y(int x0, int y0, int *xi, int *yi, double angle)
{
	int		grid_y;
	int		dy;
	int		result;
	double	d;

	angle = normalize_angle(angle);
	if (fabs(sin(angle)) < EPSILON)
		return (INT_MAX);
	if (sin(angle) > 0)
	{
		if (y0 % PX == 0)
			grid_y = y0 - PX;
		else
			grid_y = y0 - (y0 % PX);
	}
	else
		grid_y = y0 + PX - (y0 % PX);
	dy = grid_y - y0;
	d = fabs((double)dy / sin(angle));
	result = (int)round(d);
	*yi = grid_y;
	*xi = x0 + (int)round(d * cos(angle));
	if (*xi < 0 || *xi >= WIDTH * PX ||
		*yi < 0 || *yi >= HEIGHT * PX)
		return (INT_MAX);
	return (result);
}

int hit_wall(double angle, int x, int y, char **map)
{
	int	offset;
	int	tile_x;
	int	tile_y;

	offset = 1;
	if (fabs(cos(angle)) >= EPSILON)
	{
		if (cos(angle) > 0)
			x += offset;
		else
			x -= offset;
	}
	if (fabs(sin(angle)) >= EPSILON)
	{
		if (sin(angle) > 0)
			y -= offset;
		else
			y += offset;
	}
	tile_x = x / PX;
	tile_y = y / PX;
	if (tile_x < 0 || tile_y < 0 || tile_x >= WIDTH || tile_y >= HEIGHT)
		return (1);
	if (map[tile_y][tile_x] == '1')
		return (1);
	return 0;
}


int	vertical_grid(t_player *player, char **map)
{
	t_trig	trig;
	int		total;

	total = 0;
	trig.dx = distance_x(player->x, player->y, &trig.x0, &trig.y0, player->dir);
	if (trig.dx == INT_MAX)
		return (INT_MAX);
	total += trig.dx;
	if (hit_wall(player->dir, trig.x0, trig.y0, map))
		return (total);
	trig.dx = distance_x(trig.x0, trig.y0, &trig.x1, &trig.y1, player->dir);
	if (trig.dx == INT_MAX)
		return (INT_MAX);
	total += trig.dx;
	if (hit_wall(player->dir, trig.x1, trig.y1, map))
		return (total);
	trig.Yi = abs(trig.y1 - trig.y0);
	while (!hit_wall(player->dir, trig.x1, trig.y1, map))
	{
		if (cos(player->dir) > 0)
			trig.x1 += PX;
		else
			trig.x1 -= PX;
		if (sin (player->dir) > 0)
			trig.y1 -= trig.Yi;
		else
			trig.y1 += trig.Yi;
		total += trig.dx;
	}
	return (total);
}

int	horizontal_grid(t_player *player, char **map, double angle)
{
	t_trig	trig;
	int		total;
	int		wall;

	wall = 0;
	total = 0;
	trig.dy = distance_y(player->x, player->y, &trig.x0, &trig.y0, angle);
	if (trig.dy == INT_MAX)
		return (INT_MAX);
	total += trig.dy;
	if (hit_wall(player->dir, trig.x0, trig.y0, map))
		return (total);
	trig.dy = distance_y(trig.x0, trig.y0, &trig.x1, &trig.y1, angle);
	if (trig.dy == INT_MAX)
		return (INT_MAX);
	total += trig.dy;
	if (hit_wall(player->dir, trig.x1, trig.y1, map))
		return (total);
	trig.Xi = abs(trig.x1 - trig.x0);
	while (!hit_wall(player->dir, trig.x1, trig.y1, map))
	{
		if (cos(angle) > 0)
			trig.x1 += trig.Xi;
		else
			trig.x1 -= trig.Xi;
		if (sin(angle) > 0)
			trig.y1 -= PX;
		else
			trig.y1 += PX;
		total += trig.dy;
	}
	return (total);
}

void	rays_length(t_player *player, char **map)
{
	int		dx;
	int		dy;
	double	angle;

	angle = player->dir;
	dx = vertical_grid(player, map);
	dy = horizontal_grid(player, map,angle);
	if (dx < dy)
		player->rays[0] = dx;
	else
		player->rays[0] = dy;
}
