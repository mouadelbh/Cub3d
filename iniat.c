/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iniat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:57:13 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/01 22:31:17 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub3d.h"

void	init_gameconfig(t_mlx *config)
{
	config->file = NULL; // hadi hiya les lignes dyal fichier
	config->map = NULL; // hadi hiya la map kaykon fih 0 o 1 o N o S o W o E
	config->mlx = NULL; 
    config->win = NULL;
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->f = NULL;
	config->c = NULL;
	config->nb_element = 0; // hadi hiya les elements li kaykon f fichier khasso ikon 6 ola la
}
