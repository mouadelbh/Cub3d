/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 02:28:16 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/01 22:34:11 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

#define WIDTH 12
#define HEIGHT 12
#define PX 64
#define PLAYER_PX 10
#define GREEN 0x00FF00
#define RED 0xFF0000
#define BLUE 0x0000FF
#define FOV 60
#define ROTATE 5
#define PI 3.14
// playable color
// #define WALL 0x008080	// Teal
// #define FLOOR 0xFFD700	// Gold
// #define PLAYER 0xFF4500	// Orange Red
// dark grey theme
#define WALL 0x6C6C6C	// Dark Grey
#define FLOOR 0x2C2C2C	// Almost Black Grey
#define PLAYER 0xFFD700	// Bright Gold

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define WINDOW_CLOSE 17
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define PLAYER_SPEED 5

typedef struct s_img
{
	void	*img;	//image pointer in mlx
	char	*addr;	//image address in memory
	int		bits;	//bits per pixel
	int		line;	//line length
	int		end;	//endian
}	t_img;

typedef struct s_player
{
	double	x;		//player x position
	double	y;		//player y position
	double	dir;	//player direction
	double	fov;	//player field of view
	int		*rays;	//rays distance to walls
}	t_player;

typedef struct s_mlx
{
	void		*mlx;		//pointer to the mlx server
	void		*win;		//pointer to the window
	char		**map;		//map to render
	t_list		*file;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	int			nb_element;
	t_img		*img;		//frame to render
	t_img		*new_img;	//img to buffer next frame
	t_player	*player;	//window width
}	t_mlx;

int		move_right(t_mlx *mlx);
int		move_left(t_mlx *mlx);
int		move_up(t_mlx *mlx);
int		move_down(t_mlx *mlx);
int		render_game(t_mlx *mlx);
void	draw_player(t_player *player, t_img *img);
void	buffer_img(t_img *img, char **map);
void	draw_block(t_img *img, int width, int height, int color);
void	free_arr(void **arr, int size);
void	close_game(t_mlx *mlx);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_horizontal_line(t_img *img, int x, int y, int x2, int color);
void	draw_line(t_img *img, int x0, int y0, int x, int y);
void	draw_vertical_line(t_img *img, int x, int y, int y2, int color);
char	**get_map(int fd);
char	**ft_realloc(char **map, int size, int i);

/* PARSING */

// check_cubfile
int		check_file_path(char *gamefile);
void	readfile_to_list(int fd, t_mlx *config);
int		map_make(t_list *start, char ***map);
int		switch_info_to_list(t_mlx *config);
int		check_cubfile(char *gamefile, t_mlx *config);

// check_MAP
int		check_wall1(char **map, int size);
int		check_map_content(char **map, int size);
int		check_cub_content(t_mlx *config);

// valid_element
int		element_already_present(char *line, t_mlx *config);
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
void	garbage_collector(t_mlx *config);

// init_structures
void	init_gameconfig(t_mlx *config);


#endif
