/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 02:28:16 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/01/26 06:18:10 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"

#define WIDTH 12
#define HEIGHT 12
#define PX 64
#define PLAYER_PX 15
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
# define PLAYER_SPEED 10

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
}	t_player;

typedef struct s_mlx
{
	void		*mlx;		//pointer to the mlx server
	void		*win;		//pointer to the window
	char		**map;		//map to render
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
char	**get_map(int fd);
char	**ft_realloc(char **map, int size, int i);

#endif
