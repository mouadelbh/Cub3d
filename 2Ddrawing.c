/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Ddrawing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:34:03 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/01/28 11:32:56 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line + x * (img->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_horizontal_line(t_img *img, int x, int y, int x2, int color)
{
	int	i;

	i = 0;
	while (i < x2 - x)
	{
		put_pixel(img, x + i, y, color);
		i++;
	}
}

void	draw_vertical_line(t_img *img, int x, int y, int y2, int color)
{
	int	i;

	i = 0;
	while (i < y2 - y)
	{
		put_pixel(img, x, y + i, color);
		i++;
	}
}

void	draw_line(t_img *img, int x0, int y0, int x, int y)
{
	double	stepx;
	double	stepy;
	double	dx;
	double	dy;
	int		i;
	int		step;

	dx = x - x0;
	dy = y - y0;
	step = fmax(abs(dx), abs(dy));
	i = 0;
	if (dx == 0)
		draw_vertical_line(img, x0, y0, y, GREEN);
	else if (dy == 0)
		draw_horizontal_line(img, x0, y0, x, GREEN);
	else
	{
		stepx = (double)(dx / step);
		stepy = (double)(dy / step);
		while (i < step)
		{
			put_pixel(img, round(x0 + i * stepx), round(y0 + i * stepy), GREEN);
			i++;
		}
	}
}
