/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/25 17:45:55 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_cubfile(char *gamefile, t_mlx *config)
{
	int	fd;

	fd = check_file_path(gamefile);
	if (fd == -1)
		return (1);
	readfile_to_list(fd, config);
	if (switch_info_to_list(config) == -1 || check_cub_content(config) == -1)
	{
		garbage_collector(config);
		return (-1);
	}
	return (0);
}

void	find_start_position(t_mlx *config)
{
	char	**map;
	int		x;
	int		y;

	y = -1;
	map = config->map;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
			|| map[y][x] == 'W')
			{
				config->player.start_pos = map[y][x];
				map[y][x] = '0';
				config->player.pos_x = y + 0.5;
				config->player.pos_y = x + 0.5;
				break ;
			}
		}
	}
}

void	init_dir_plane(t_mlx *config)
{
	if (config->player.start_pos == 'N')
	{
		config->player.dir_x = -1;
		config->player.plane_y = 0.52359877559;
	}
	if (config->player.start_pos == 'S')
	{
		config->player.dir_x = 1;
		config->player.plane_y = -0.52359877559;
	}
	if (config->player.start_pos == 'W')
	{
		config->player.dir_y = -1;
		config->player.plane_x = -0.52359877559;
	}
	if (config->player.start_pos == 'E')
	{
		config->player.dir_y = 1;
		config->player.plane_x = 0.52359877559;
	}
}

void	get_c_or_f_info(char *str, int tab[3])
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == ','))
		i++;
	tab[0] = ft_atoi(str + i);
	while (ft_isdigit(str[i]) != 0)
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == ','))
		i++;
	tab[1] = ft_atoi(str + i);
	while (ft_isdigit(str[i]) != 0)
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == ','))
		i++;
	tab[2] = ft_atoi(str + i);
}

void	update_cubconfig(t_mlx *config)
{
	find_start_position(config);
	init_dir_plane(config);
	get_c_or_f_info(config->c, config->draw.c);
	get_c_or_f_info(config->f, config->draw.f);
}
