/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:19:02 by jotong            #+#    #+#             */
/*   Updated: 2026/03/01 14:35:27 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef VIEWPORT_HEIGHT
#  define VIEWPORT_HEIGHT 6
# endif

# ifndef VIEWPORT_WIDTH
#  define VIEWPORT_WIDTH 15
# endif

# ifndef SPRITE_SIZE
#  define SPRITE_SIZE 128
# endif

# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# ifdef __linux__
#  include <X11/keysym.h>
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
#  define KEY_ESC XK_Escape
# elif __APPLE__
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
# endif

typedef struct s_img {
    void    *img_ptr;
    char    *addr;        // The actual raw pixel data
    int     bits_per_pixel;
    int     line_length;  // Number of bytes in one row
    int     endian;
} t_img;

typedef struct s_ray
{
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  wall_dist;
    int     step_x;
    int     step_y;
    int     side; // 0 for NS wall, 1 for EW wall
}   t_ray;

typedef struct s_map // from solong
{
	int		h;
	int		w;
	int		start;
	int		exit;
	int		fd;
	int		p_start_x;
	int		p_start_y;
	char	**grid;
}	t_map;

typedef struct s_texture { // TODO: initialize this
    void    *img;          // Pointer from mlx_xpm_file_to_image
    char    *addr;         // Pointer from mlx_get_data_addr
    int     width;
    int     height;
    int     line_len;
    int     bpp;
    int     endian;
} t_texture;

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    t_map   map_info;    // Texture paths, colors, and 2D map
    t_player player;     // Pos, Dir, Plane
    t_img    img;        // The frame buffer to push to the window
} t_data;

typedef struct s_game // from solong
{
	void		*mlx;
	void		*window;
	char        *tex_paths[4]; // Stores paths "./textures/north.xpm". has 4 slots
    t_texture   textures[4];   // Stores the actual pixel data. has 4 slots
    int         floor_color;   // Hexadecimal color
    int         ceiling_color; // Hexadecimal color
	int			view_w;
	int			view_h;
	int			p_x;  // player current position (x_axis)
	int			p_y; // player current position (y_axis)
    int         p_dir;  // direction that the player is facing
    
	char		*mp;
    t_data      *data;   
	t_map		*map;
}	t_game;

typedef struct s_queue // from solong
{
	t_pos	q[10000];
	int		front;
	int		back;
	int		**dir;
}	t_queue;

int	        char_arr_size(char **arr);
void		get_map_edges(t_game **game, char *f_map);
void		calculate_viewable_area(t_game **game);
void 		cleanup_game(t_game *game);
void 		free_checked(int **checked, int height);
void	    free_array(char **arr);
void		init_grid( char *f_map, t_game **game);
void		init_game(t_game **game, char *f_map);
void		initialise_map_values(t_game **game, char *f_map);
int			close_window(void *game);
void		destroy_images(t_game **game);
int			get_map_height(char	*f_map);
int			check_asset(char *f_str, t_game **game);
void		load_map(char *f_map, t_game **game);
void		reload_map(t_game **game, int prev_x, int prev_y);
void		show_images(t_game *game);
void		show_background(t_game *game);
void		show_collectible(t_game *game);
void		show_exit(t_game *game, int state);
void		show_player(t_game *game);
void		redraw_player(t_game *game);
void		show_walls(t_game *game);
void		print_map(t_map *map);
void		render_map(t_game **game);
void		render_viewable_map(t_game **game);
void		set_view_dimensions(t_game **game);
int			handle_keypress(int keycode, void *game);
void		check_update_element_ctr(t_game **game, char c, int *pos);
void		free_and_exit(t_game **game, int status, char *msg);
int			path_check(char **grid, t_game **game);
void		free_mlx(t_game **game);
int			parse_cub_file(char *file, t_game **game);
int	        check_asset_tex(char *f_str, t_game **game);
int         check_asset_colour(char *f_str, t_game **game);


#endif