/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:23:30 by jotong            #+#    #+#             */
/*   Updated: 2026/02/22 12:24:18 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// render.c: Logic for drawing vertical stripes on the screen.


#include "so_long.h"
#include "libft.h"
#ifdef __APPLE__
# include "minilibx_opengl_20191021/mlx.h"
#elif __linux__
# include "minilibx-linux/mlx.h"
#endif

int	close_window(void *game) // from solong
{
	t_game	*game_tmp;

	game_tmp = (t_game *)game;
	if (game_tmp && game_tmp->mlx && game_tmp->window)
	{
		mlx_destroy_window(game_tmp->mlx, game_tmp->window);
		ft_printf("freeing memory after destroying window\n");
		game_tmp->window = NULL;
	}
	free_and_exit(game_tmp->mem_p, &game_tmp, 0, "Window closed.");
	return (0);
}

static void	*create_window(t_pool *mem_p, t_game **game, void *mlx) // from solong
{
	int		width;
	int		height;

	width = ((*game)->view_w) * SPRITE_SIZE;
	height = ((*game)->view_h) * SPRITE_SIZE;
	(*game)->window = mlx_new_window(mlx, width, height, "so_long");
	if (!(*game)->window)
		free_and_exit(mem_p, game, 1, "Failed to open new window.\n");
	return ((*game)->window);
}

void	show_images(t_game *game) // from solong
{
	show_background(game);
	show_walls(game);
	show_exit(game, 1);
	show_collectible(game);
	show_player(game);
}

int	handle_close(void *game_in) // from solong
{
	t_game	*game;

	game = (t_game *)game_in;
	close_window(game);
	return (0);
}

void	render_map(t_pool **mem_p, t_game **game) // from solong
{
	(*game)->window = create_window(*mem_p, game, (*game)->mlx);
	show_images((*game));
	render_viewable_map(game);
	mlx_key_hook((*game)->window, handle_keypress, *game);
	mlx_hook((*game)->window, 17, 0, handle_close, *game);
}


void	calculate_viewable_area(t_game **game) // from solong
{
	if ((*game)->map->w > VIEWPORT_WIDTH)
	{
		(*game)->v_y = (*game)->p_y - VIEWPORT_WIDTH / 2;
		if ((*game)->v_y < 0)
			(*game)->v_y = 0;
		if ((*game)->v_y + VIEWPORT_WIDTH > (*game)->map->w)
			(*game)->v_y = (*game)->map->w - VIEWPORT_WIDTH;
	}
	else
		(*game)->v_y = 0;
	if ((*game)->map->h > VIEWPORT_HEIGHT)
	{
		(*game)->v_x = (*game)->p_x - VIEWPORT_HEIGHT / 2;
		if ((*game)->v_x < 0)
			(*game)->v_x = 0;
		if ((*game)->v_x + VIEWPORT_HEIGHT > (*game)->map->h)
			(*game)->v_x = (*game)->map->h - VIEWPORT_HEIGHT;
	}
	else
		(*game)->v_x = 0;
}

static void	put_relevant_image(t_game **game, int *ctr, int *mp, char tile) // from solong
{
	if (tile == '1')
		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->w_img,
			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
	if (tile == 'C')
		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->c_img,
			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
	if (tile == 'E' && (*game)->c_count == (*game)->map->c
		&& mp[0] == (*game)->p_x && mp[1] == (*game)->p_y)
		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->e2_img,
			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
	else if (tile == 'E')
		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->e_img,
			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
	if (tile == '0')
		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->bg_img,
			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
}

void	render_viewable_map(t_game **game) // from solong
{
	int		mp[2];
	int		ctr[2];
	char	tile;

	ctr[0] = 0;
	while (ctr[0] < (*game)->view_h)
	{
		ctr[1] = 0;
		while (ctr[1] < (*game)->view_w)
		{
			mp[0] = (*game)->v_x + ctr[0];
			mp[1] = (*game)->v_y + ctr[1];
			if (mp[0] >= 0 && mp[0] < (*game)->map->h && mp[1] >= 0
				&& mp[1] < (*game)->map->w)
			{
				tile = (*game)->map->grid[mp[0]][mp[1]];
				put_relevant_image(game, ctr, mp, tile);
			}
			ctr[1]++;
		}
		ctr[0]++;
	}
}

void	reload_map(t_game **game, int prev_x, int prev_y) // from solong
{
	calculate_viewable_area(game);
	if ((*game)->map->grid[prev_x][prev_y] == 'C')
	{
		(*game)->c_count += 1;
		(*game)->map->grid[prev_x][prev_y] = '0';
	}
	render_viewable_map(game);
	redraw_player(*game);
}

void	set_view_dimensions(t_game **game)
{
	if ((*game)->map->w < VIEWPORT_WIDTH)
		(*game)->view_w = (*game)->map->w;
	else
		(*game)->view_w = VIEWPORT_WIDTH;
	if ((*game)->map->h < VIEWPORT_HEIGHT)
		(*game)->view_h = (*game)->map->h;
	else
		(*game)->view_h = VIEWPORT_HEIGHT;
}


void	show_background(t_game *game) // from solong
{
	void	*bg;
	int		bg_edge;

	bg_edge = 32;
	bg = mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm",
			&bg_edge, &bg_edge);
	game->bg_img = bg;
}

void	show_walls(t_game *game)
{
	void	*wall;
	int		wall_edge;

	wall_edge = 32;
	wall = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm",
			&wall_edge, &wall_edge);
	game->w_img = wall;
}

void	show_exit(t_game *game, int state) // from solong
{
	void	*exit;
	int		exit_edge;

	exit_edge = 32;
	if (state == 1)
		exit = mlx_xpm_file_to_image(game->mlx, "assets/door.xpm",
				&exit_edge, &exit_edge);
	else
		exit = mlx_xpm_file_to_image(game->mlx, "assets/door_open.xpm",
				&exit_edge, &exit_edge);
	game->e2_img = mlx_xpm_file_to_image(game->mlx, "assets/player_door_c.xpm",
			&exit_edge, &exit_edge);
	game->e_img = exit;
}

void	show_collectible(t_game *game) // from solong
{
	void	*c;
	int		c_edge;

	c_edge = 32;
	c = mlx_xpm_file_to_image(game->mlx, "assets/collectible.xpm",
			&c_edge, &c_edge);
	game->c_img = c;
}


void	check_update_element_ctr(t_pool *mem_p, t_game **game, char c, int *pos) // from solong
{
	if (c == 'C')
		(*game)->map->c += 1;
	else if (c == 'P')
	{
		(*game)->map->start += 1;
		(*game)->map->p_start_x = pos[0];
		(*game)->map->p_start_y = pos[1];
		(*game)->p_x = pos[0];
		(*game)->p_y = pos[1];
	}
	else if (c == 'E')
		(*game)->map->exit += 1;
	else if (!(c == '1' || c == '0' || c == 'E' || c == 'P' || c == 'C'))
		free_and_exit(mem_p, game, 1, "Invalid item found in map.\n");
	if ((*game)->map->start > 1)
		free_and_exit(mem_p, game, 1, "More than one start pos found.\n");
	else if ((*game)->map->exit > 1)
		free_and_exit(mem_p, game, 1, "More than one exit found.\n");
}

void	print_map(t_map *map) // from solong
{
	int	i;
	int	j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			ft_printf("%c", map->grid[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
}

void	get_map_edges(t_game **game, char *f_map) // from solong
{
	int		h;
	int		w;
	int		fd;
	char	*line;

	h = 0;
	w = 0;
	if (!f_map)
		return ;
	fd = open(f_map, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL && *line != '\n')
	{
		w = ft_strlen(line);
		if (line[w - 1] != '\n')
			w += 1;
		h++;
		free(line);
		line = get_next_line(fd);
	}
	(*game)->map->h = h;
	(*game)->map->w = w;
	free(line);
	line = NULL;
	close(fd);
}

int	check_asset_exist(char *f_name) // from solong
{
	int	fd;
	int	result;

	fd = open(f_name, O_RDONLY);
	result = fd;
	close(fd);
	return (result);
}

