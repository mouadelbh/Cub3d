/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 02:28:16 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/26 22:58:53 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_W 800
# define SCREEN_H 800
# define ROT_SPEED 0.0325
# define MOV_SPEED 0.30

typedef struct s_imge
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		ll;
	int		ed;
}				t_imge;

typedef struct s_player
{
	char	start_pos;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	mov_x;
	double	mov_y;		
}			t_player;

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

typedef struct s_draw
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	t_imge	*txt_no;
	t_imge	*txt_so;
	t_imge	*txt_we;
	t_imge	*txt_ea;
	int		c[3];
	int		f[3];
	double	wall_x;
	int		txt_x;
}		t_draw;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	char		**map;
	t_list		*file;
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
}			t_mlx;

/* PARSING */

// check_cubfile
int			check_file_path(char *gamefile);
void		readfile_to_list(int fd, t_mlx *config);
int			map_make(t_list *start, char ***map);
int			switch_info_to_list(t_mlx *config);
int			check_cubfile(char *gamefile, t_mlx *config);

// check_MAP
int			check_wall1(char **map, int size);
int			check_map_content(char **map, int size);
int			check_cub_content(t_mlx *config);

// valid_element
int			element_already_present(char *line, t_mlx *config);
int			with_correct_info(char *line);
int			valid_element(char *line);

// is_surrounded_by_WALLS
int			is_surrounded_by_walls(char **map, int size, int i, int j);

// parssing_TOOLS
int			prblem(char *msg1, char *msg2, char *msg3);
int			find_size(t_list *start);
int			is_start_map(char *line);
int			is_empty_line(char *line);
char		*dlt_spaces(char *line);
char		*ft_strim_path(char *path);
void		garbage_collector(t_mlx *config);

// free 
void		destroye_img(t_mlx *config, t_draw *d);
void		free_ptr_img(t_mlx *config);

// init_structures
void		init_cubconfig(t_mlx *config);

/* RAYCASTING */
int			check_cubfile(char *gamefile, t_mlx *config);
void		find_start_position(t_mlx *config);
void		init_dir_plane(t_mlx *config);
void		get_c_or_f_info(char *str, int tab[3]);
void		update_cubconfig(t_mlx *config);
t_imge		*load_img(void *mlx, char *path);
int			load_all_texture(t_mlx *config, t_draw *d);
void		ft_dda(t_ray *r, char **map);
void		update_side(t_ray *r, t_player *ply);
void		creat_ray(t_ray *r, t_player *ply, int x);
void		dist_ply_wall(t_ray *r, t_player *p);
void		draw_up_down(t_draw *d, t_ray *r);
t_imge		*find_txt_dir(t_mlx *c);
void		l3bar_wall(t_mlx *c, t_imge *txt);
int			find_txt_pixel_color(t_imge *txt, int x, int y);
void		my_mlx_pixel_put(t_imge *img, int x, int y, int color);
int			find_color(int r, int g, int b);
int			*put_pixel_color_colm(t_mlx *c, t_imge *txt);
int			put_pixel_col(t_mlx *c, t_imge *txt, int x);
void		loop_ray(t_mlx *config);
int			mouse_hook(void *param);
void		display(t_mlx *config, t_imge *img);
void		rotation_camera(int keysym, t_mlx *config, t_player *p);
void		move_player_ns(int keysym, t_mlx *config, t_player *p);
void		move_player_we(int keysym, t_mlx *config, t_player *p);

#endif
