/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/25 17:45:15 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_ptr_img(t_mlx *config)
{
	if (config->draw.txt_no)
		free(config->draw.txt_no);
	if (config->draw.txt_so)
		free(config->draw.txt_so);
	if (config->draw.txt_we)
		free(config->draw.txt_we);
	if (config->draw.txt_ea)
		free(config->draw.txt_ea);
}

void	destroye_img(t_mlx *config, t_draw *d)
{
	if (d->txt_no)
		mlx_destroy_image(config->mlx, d->txt_no->img);
	if (d->txt_so)
		mlx_destroy_image(config->mlx, d->txt_so->img);
	if (d->txt_we)
		mlx_destroy_image(config->mlx, d->txt_we->img);
	if (d->txt_ea)
		mlx_destroy_image(config->mlx, d->txt_ea->img);
}
