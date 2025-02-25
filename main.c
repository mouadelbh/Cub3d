/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 01:22:36 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/25 17:44:31 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	key_hook(int keysym, t_mlx *config)
{
	t_player	*p;

	p = &config->player;
	if (keysym == XK_Escape)
	{
		garbage_collector(config);
		exit(0);
	}
	rotation_camera(keysym, config, p);
	move_player_ns(keysym, config, p);
	move_player_we(keysym, config, p);
	if (keysym == XK_w || keysym == XK_s || keysym == XK_a || keysym == XK_d)
		display(config, &config->img);
	return (0);
}

void	game_loop(t_mlx *config, t_imge *img)
{
	config->mlx = mlx_init();
	config->win = mlx_new_window(config->mlx, SCREEN_W, SCREEN_H, "cub4d");
	img->img = mlx_new_image(config->mlx, SCREEN_W, SCREEN_H);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->ed);
	if (load_all_texture(config, &config->draw) == -1)
	{
		garbage_collector(config);
		exit(1);
	}
	display(config, img);
	mlx_hook(config->win, KeyPress, KeyPressMask, key_hook, config);
	mlx_hook(config->win, 17, 0, mouse_hook, config);
	mlx_loop(config->mlx);
}

int	main(int ac, char **av, char **env)
{
	t_mlx	mlx;

	mlx.mlx = NULL;
	mlx.win = NULL;
	if (env && !env[0])
		return (prblem("error!\n", "environement NULL", "    *__*\n"));
	init_cubconfig(&mlx);
	if (ac == 2 && av[1] && av[1][0] != '\0')
	{
		if (check_cubfile(av[1], &mlx) != 0)
			return (1);
		update_cubconfig(&mlx);
		game_loop(&mlx, &mlx.img);
	}
	else
		ft_putstr_fd("Error!\nParameter not valid\n", 2);
	return (0);
}
