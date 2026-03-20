/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:19:02 by jotong            #+#    #+#             */
/*   Updated: 2026/03/20 16:19:13 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef HEIGHT
#  define HEIGHT 6
# endif

# ifndef WIDTH
#  define WIDTH 15
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
# include "libft.h"

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

typedef struct s_pos
{
    int x;
    int y;
}   t_pos;

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
	int		fd;
    int     start;
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

typedef struct s_player
{
    // Position on the map
    double  pos_x;
    double  pos_y;

    // Direction vector (Where the player is looking)
    // Always has a length of 1 (a unit vector)
    double  dir_x;
    double  dir_y;

    // Camera plane vector (Determines the Field of View)
    // Must be perpendicular to the direction vector
    double  plane_x;
    double  plane_y;

    // Movement state (Optional, but great for smooth multi-key movement)
    int     move_up;
    int     move_down;
    int     move_left;
    int     move_right;
    int     rotate_left;
    int     rotate_right;

    // Speed constants
    double  move_speed;
    double  rot_speed;
}   t_player;

// typedef struct s_data {
//     void    *mlx_ptr;
//     void    *win_ptr;
//     t_map   map_info;    // Texture paths, colors, and 2D map
//     t_player player;     // Pos, Dir, Plane
//     t_img    img;        // The frame buffer to push to the window
// } t_data;

typedef struct s_game // from solong
{
	void		*mlx_ptr;
	void		*win_ptr;
	char        **tex_paths; // Stores paths "./textures/north.xpm". has 4 slots
    t_texture   textures[4];   // Stores the actual pixel data. has 4 slots
    int         floor_colour;   // Hexadecimal color
    int         ceiling_colour; // Hexadecimal color
	int			view_w;
	int			view_h;
    t_list      *tmp_list;
    t_img       img;
	char		*mp;
    t_player	player;   
	t_map		*map;
}	t_game;

typedef struct s_queue // from solong
{
	t_pos	q[10000];
	int		front;
	int		back;
	int		**dir;
}	t_queue;

void	    close_file(int fd);
int			arr_in_limit(int n, int min, int max);
int	        char_arr_size(char **arr);
void		get_map_edges(t_game **game, char *f_map);
// void		calculate_viewable_area(t_game **game);
void 		cleanup_game(t_game *game);
void 		free_checked(int **checked, int height);
void	    free_array(char **arr);
void        init_grid(t_game **game);
void		init_game(t_game **game, char *f_map);
int			close_window(void *game);
void		destroy_images(t_game **game);
int			get_map_height(char	*f_map);
int			check_asset(char *f_str, t_game **game);
void	    load_map(char *f_map, t_game **game);
void		reload_map(t_game **game, int prev_x, int prev_y);
void		show_images(t_game *game);
// void		show_collectible(t_game *game);
// void		show_exit(t_game *game, int state);
void		show_player(t_game *game);
void		redraw_player(t_game *game);
void		show_walls(t_game *game);
void		print_map(t_map *map);
void		render_map(t_game **game);
// void		render_viewable_map(t_game **game);
void		set_view_dimensions(t_game **game);
int			handle_keypress(int keycode, void *game);
void		check_update_element_ctr(t_game **game, char c, int *pos);
void		free_and_exit(t_game **game, int status, char *msg);
int			path_check(t_game **game);
void		free_mlx(t_game **game);
int			parse_cub_file(char *file, t_game **game);
int	        check_asset_tex(char *f_str, t_game **game);
int         check_asset_colour(char *f_str, t_game **game);
int 		move_player(t_game **game, double move_x, double move_y);
void        *create_window(t_game **game, void *mlx);
void	    update_player_direction(t_game **game, char c);
t_list	    *create_tmp_list(char *map_row);
void        copy_map_to_grid(t_game **game);
int	        add_row_to_list(t_list **list, char *map_row);
int	        populate_row(t_game **game, int row, char *line);
void	    render_raycast(t_game *game);
void	    free_fd_map(t_game **game);
void		free_safely(char **line);
int	        initialise_textures(t_game **game);
int         is_map_closed(t_game *game);

#endif