/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 01:22:36 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/27 17:52:15 by mel-bouh         ###   ########.fr       */
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
	if ( x < last)
	{
		p->m_left = 1;
		p->m_right = 0;
		last = x;
	}
	else if ( x > last)
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

int	render_game(t_mlx *config)
{
	t_player	*p;
	static int	i;

	p = &config->player;
	if (i > 100 && (p->m_left || p->m_right))
	{
		p->m_left = 0;
		p->m_right = 0;
		i = 0;
	}
	if (p->m_right || p->m_left || p->r_left || p->r_right)
	{
		rotation_camera(p);
		i++;
	}
	if (p->up || p->down)
		move_player_ns(config, p);
	if (p->right || p->left)
		move_player_we(config, p);
	if (p->m_right || p->m_left ||p->r_right || p->r_left || p->up || p->down || p->right || p->left)
		display(config, &config->img);
	return (0);
}

void	game_loop(t_mlx *config, t_imge *img)
{
	config->mlx = mlx_init();
	config->win = mlx_new_window(config->mlx, SCREEN_W, SCREEN_H, "CUB3D");
	img->img = mlx_new_image(config->mlx, SCREEN_W, SCREEN_H);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->ed);
	if (load_all_texture(config, &config->draw) == -1)
	{
		garbage_collector(config);
		exit(1);
	}
	display(config, img);
	mlx_hook(config->win, KeyPress, KeyPressMask, key_hook, config);
	mlx_hook(config->win, KeyRelease, KeyReleaseMask, key_release, config);
	mlx_hook(config->win, MotionNotify, PointerMotionMask, mouse_hook, config);
	mlx_hook(config->win, 17, 0, esc_hook, config);
	mlx_loop_hook(config->mlx, render_game, config);
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
