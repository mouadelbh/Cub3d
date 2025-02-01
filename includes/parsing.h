/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:13:42 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/01 11:46:34 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../libft/libft.h"

# define SCREEN_W 640
# define SCREEN_H 480
# define ROT_SPEED 0.045
# define MOV_SPEED 0.45

// ->bpp = bit_by_pixels
// ->ll = line_length
// ->ed = endian => indique l'ordre d'interpretation des octets

// typedef struct s_imge
// {
// 	void	*img;
// 	char	*addr;
// 	int		width;
// 	int		height;
// 	int		bpp;
// 	int		ll;
// 	int		ed;
// }				t_imge;

// typedef struct s_player
// {
// 	char	start_pos;
// 	double	pos_x;
// 	double	pos_y;
// 	double	dir_x;
// 	double	dir_y;
// 	double	plane_x;
// 	double	plane_y;
// 	double	camera_x;
// 	double	mov_x;
// 	double	mov_y;
// }			t_player;

// player rah bayn ash kaydir f l'ecran
// darori position dyal player tbdel f l'ecran , dirction dyal player tbdel f l'ecran
// w plane dyal player tbdel f l'ecran
// w camera_x dyal player tbdel f l'ecran
// w mov_x w mov_y dyal player tbdel f l'ecran walakin wash hadshi ghay

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	ray_x;
	double	ray_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	p_w_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}			t_ray;

// typedef struct s_draw
// {
// 	int		wall_height;
// 	int		draw_start;
// 	int		draw_end;
// 	t_imge	*txt_no;
// 	t_imge	*txt_so;
// 	t_imge	*txt_we;
// 	t_imge	*txt_ea;
// 	int		c[3];
// 	int		f[3];
// 	double	wall_x;
// 	int		txt_x;
// }		t_draw;

typedef struct s_gameconfig
{
	t_list		*file;
	char		**map;
	void		*mlx;
	void		*mlx_w;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	int			nb_element;
	t_player	player;
	t_ray		ray;
	t_draw		draw;
	t_imge		img;
}				t_cubconfig;

/** PARSSING **/

// check_cubfile
int		check_file_path(char *gamefile);
void	readfile_to_list(int fd, t_cubconfig *config);
int		map_make(t_list *start, char ***map);
int		switch_info_to_list(t_cubconfig *config);
int		check_cubfile(char *gamefile, t_cubconfig *config);

// check_MAP
int		check_wall(char **map, int size);
int		check_map_content(char **map, int size);
int		check_cub_content(t_cubconfig *config);

// valid_element
int		element_already_present(char *line, t_cubconfig *config);
int		with_correct_info(char *line);
int		valid_element(char *line);

// is_surrounded_by_WALLS
int		is_surrounded_by_walls(char **map, int size, int i, int j);

// parssing_TOOLS
int     prblem(char *msg1, char *msg2, char *msg3);
int		find_size(t_list *start);
int		is_start_map(char *line);
int		is_empty_line(char *line);
char	*dlt_spaces(char *line);
char	*ft_strim_path(char *path);

// init_structures
void	init_gameconfig(t_cubconfig *config);


#endif
