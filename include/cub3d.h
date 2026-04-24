/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3d.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jotong <jotong@student.42singapore.sg>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/18 16:19:02 by jotong			#+#	#+#			 */
/*   Updated: 2026/04/24 21:37:49 by jotong		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef HEIGHT
#  define HEIGHT 460
# endif

# ifndef WIDTH
#  define WIDTH 640
# endif

# ifdef __linux__
#  define ENV 1
# elif __APPLE__
#  define ENV 2
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
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# elif __APPLE__
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# endif

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

typedef struct s_pos
{
	int		row;
	int		col;
}	t_pos;

typedef struct s_map
{
	int		h;
	int		w;
	int		fd;
	int		start;
	char	**grid;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		line_len;
	int		bpp;
	int		endian;
}	t_texture;

typedef struct s_player
{
	// Position on the map
	double	pos_x;
	double	pos_y;

	// Direction vector (Where the player is looking)
	// Always has a length of 1 (a unit vector)
	double	dir_x;
	double	dir_y;

	// Camera plane vector (Determines the Field of View)
	// Must be perpendicular to the direction vector
	double	plane_x;
	double	plane_y;

	// Movement state
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;

	// Speed constants
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**tex_paths;
	t_texture	textures[4];
	int			floor_colour;
	int			ceiling_colour;
	int			view_w;
	int			view_h;
	t_list		*tmp_list;
	t_img		img;
	char		*mp;
	t_player	player;
	t_map		*map;
}	t_game;

typedef struct s_queue
{
	t_pos	*items;
	int		front;
	int		back;
	int		**dir;
}	t_queue;

void		close_file(int fd);
int			arr_in_limit(int n, int min, int max);
int			char_arr_size(char **arr);
void		get_map_edges(t_game **game, char *f_map);
void		cleanup_game(t_game *game);
void		free_checked(int **checked, int height);
void		free_array(char **arr);
void		init_grid(t_game **game);
void		init_game(t_game **game, char *f_map);
int			close_window(void *game);
void		destroy_images(t_game **game);
int			check_asset(char *f_str, t_game **game);
void		load_map(char *f_map, t_game **game, char *line);
void		print_map(t_map *map);
int			handle_keypress(int keycode, void *game);
void		check_update_element_ctr(t_game **game, char c, int *pos);
void		free_and_exit(t_game **game, int status, char *msg);
void		free_mlx(t_game **game);
int			parse_cub_file(char *file, t_game **game);
int			check_asset_tex(char *f_str, t_game **game);
int			check_asset_colour(char *f_str, t_game **game);
int			move_player(t_game **game);
void		*create_window(t_game **game, void *mlx);
void		update_player_direction(t_game **game, char c);
t_list		*create_tmp_list(char *map_row);
void		copy_map_to_grid(t_game **game);
int			add_row_to_list(t_list **list, char *map_row);
int			populate_row(t_game **game, int row, char *line);
void		populate_grid(t_game **game, int fd, char *line);
int			initialise_textures(t_game **game);
int			is_map_closed(t_game *game);
int			render_raycast(t_game *game);
void		calculate_ray(t_game *game, t_ray *ray, int x);
void		init_dda(t_game *game, t_ray *ray);
void		perform_dda(t_game **game, t_ray *ray);
int			key_press(int keycode, void *game_in);
int			key_release(int keycode, void *game_in);
void		calculate_wall_dist(t_game *game, t_ray *ray);
int			init_ray_dims(t_game **game, t_ray *ray, int x);
void		render_vertical_line(t_game *game, t_ray *ray, int x);
void		my_mlx_pixel_put(t_game *game, int x, int y, int color);
t_texture	*select_texture(t_game *game, t_ray *ray);
int			get_texture_pixel(t_game *game, t_ray *ray, int y, int line_h);
int			handle_rotation(t_game *game);
void		set_ray(t_game *game, t_ray **ray);

#endif