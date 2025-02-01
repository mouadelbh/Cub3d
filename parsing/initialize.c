/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:57:13 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/01 11:43:52 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_imge(t_imge *imge)
{
	imge->img = NULL;
	imge->addr = NULL;
	imge->width = 0;
	imge->height = 0;
	imge->bpp = 0; // iwa hadi hiya bit per pixel.
	imge->ll = 0; // o hadi hiya line length bash n3aytoha b width dyal limage.
	imge->ed = 0; // hadik hiya endianess it indicates the byte order of the pixel color value.
}

static void	init_ray(t_ray *r)
{
	r->map_x = 0;
	r->map_y = 0;
	r->ray_x = 0.0;
	r->ray_y = 0.0;
	r->delta_x = 0.0;
	r->delta_y = 0.0;
	r->side_x = 0;
	r->side_y = 0;
	r->p_w_dist = 0; // hada khissane distance between two points
	r->step_x = 0;
	r->step_y = 0;
	r->hit = 0;
	r->side = 0;
	// nshr7 lik hadi hiya les variables li kayna f ray structure
	// bash n3aytohom b les variables li kayna f player structure
	// like delta hiya distance between two points
	// like side hiya side of the wall b7al left or right
	// like step hiya step of the ray b7al 1 or -1 wakila
	// like hit hiya if the ray hit the wall or not
	// baraka 3lik khoya !
}

void	init_gameconfig(t_cubconfig *config)
{
	config->file = NULL; // hadi hiya les lignes dyal fichier
	config->map = NULL; // hadi hiya la map kaykon fih 0 o 1 o N o S o W o E
	config->mlx = NULL;
	config->mlx_w = NULL;
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->f = NULL;
	config->c = NULL;
	config->nb_element = 0; // hadi hiya les elements li kaykon f fichier khasso ikon 6 ola la
	config->player.pos_x = 0.0;
	config->player.pos_y = 0.0;
	config->player.dir_x = 0;
	config->player.dir_y = 0;
	config->player.plane_x = 0;
	config->player.plane_y = 0;
	config->player.camera_x = 0;
	init_ray(&config->ray);
	init_imge(&config->img);
}
