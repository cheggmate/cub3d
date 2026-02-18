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


typedef struct s_map // from solong
{
	int		h;
	int		w;
	int		c;
	int		start;
	int		exit;
	int		fd;
	int		p_start_x;
	int		p_start_y;
	char	**grid;
}	t_map;

typedef struct s_game // from solong
{
	void	*mlx;
	void	*window;
	void	*p_img;
	void	*c_img;
	void	*w_img;
	void	*bg_img;
	void	*e_img;
	void	*e2_img;
	int		c_count;
	int		n_mvmts;
	int		v_x;
	int		v_y;
	int		view_w;
	int		view_h;
	int		p_x;
	int		p_y;
	char	*mp;
	int		won;
	t_map	*map;
	t_pool	*mem_p;
}	t_game;

typedef struct s_pos // from solong
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_queue // from solong
{
	t_pos	q[10000];
	int		front;
	int		back;
	int		**dir;
}	t_queue;

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    t_map   map_info;    // Texture paths, colors, and 2D map
    t_player player;     // Pos, Dir, Plane
    t_img    img;        // The frame buffer to push to the window
} t_data;

#endif