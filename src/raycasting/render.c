/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:23:30 by jotong            #+#    #+#             */
/*   Updated: 2026/03/21 16:39:43 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// render.c: Logic for drawing vertical stripes on the screen.

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

int	close_window(void *game) // from solong
{
	t_game	*game_tmp;

	game_tmp = (t_game *)game;
	if (game_tmp && game_tmp->mlx_ptr && game_tmp->win_ptr)
	{
		mlx_destroy_window(game_tmp->mlx_ptr, game_tmp->win_ptr);
		ft_printf("freeing memory after destroying window\n");
		game_tmp->win_ptr = NULL;
	}
	free_and_exit(&game_tmp, 0, "Window closed.");
	return (0);
}

void	*create_window(t_game **game, void *mlx) // from solong
{
	int		width;
	int		height;

	width = ((*game)->view_w) * SPRITE_SIZE;
	height = ((*game)->view_h) * SPRITE_SIZE;
	(*game)->win_ptr = mlx_new_window(mlx, width, height, "so_long");
	if (!(*game)->win_ptr)
		free_and_exit(game, 1, "Failed to open new window.\n");
	return ((*game)->win_ptr);
}

void	show_images(t_game *game) // TODO: add flows to render here
{
	(void)game;
	// show_walls(game);
	// show_exit(game, 1);
	// show_player(game);
}

int	handle_close(void *game_in) // from solong
{
	t_game	*game;

	game = (t_game *)game_in;
	close_window(game);
	return (0);
}

// void	render_map(t_game **game) // from solong
// {
// 	(*game)->win_ptr = create_window(game, (*game)->mlx_ptr);
// 	show_images((*game));
// 	// render_viewable_map(game);
// 	mlx_key_hook((*game)->win_ptr, handle_keypress, *game);
// 	mlx_hook((*game)->win_ptr, 17, 0, handle_close, *game);
// }


// void	calculate_viewable_area(t_game **game) // from solong
// {
// 	if ((*game)->map->w > WIDTH)
// 	{
// 		(*game)->v_y = (*game)->p_y - WIDTH / 2;
// 		if ((*game)->v_y < 0)
// 			(*game)->v_y = 0;
// 		if ((*game)->v_y + WIDTH > (*game)->map->w)
// 			(*game)->v_y = (*game)->map->w - WIDTH;
// 	}
// 	else
// 		(*game)->v_y = 0;
// 	if ((*game)->map->h > HEIGHT)
// 	{
// 		(*game)->v_x = (*game)->p_x - HEIGHT / 2;
// 		if ((*game)->v_x < 0)
// 			(*game)->v_x = 0;
// 		if ((*game)->v_x + HEIGHT > (*game)->map->h)
// 			(*game)->v_x = (*game)->map->h - HEIGHT;
// 	}
// 	else
// 		(*game)->v_x = 0;
// }

// static void	put_relevant_image(t_game **game, int *ctr, int *mp, char tile) // from solong
// {
// 	if (tile == '1')
// 		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->w_img,
// 			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
// 	if (tile == 'E' && (*game)->c_count == (*game)->map->c
// 		&& mp[0] == (*game)->p_x && mp[1] == (*game)->p_y)
// 		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->e2_img,
// 			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
// 	else if (tile == 'E')
// 		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->e_img,
// 			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
// 	if (tile == '0')
// 		mlx_put_image_to_window((*game)->mlx, (*game)->window, (*game)->bg_img,
// 			SPRITE_SIZE * ctr[1], SPRITE_SIZE * ctr[0]);
// }

// void	render_viewable_map(t_game **game) // from solong
// {
// 	int		mp[2];
// 	int		ctr[2];
// 	char	tile;

// 	ctr[0] = 0;
// 	while (ctr[0] < (*game)->view_h)
// 	{
// 		ctr[1] = 0;
// 		while (ctr[1] < (*game)->view_w)
// 		{
// 			mp[0] = (*game)->v_x + ctr[0];
// 			mp[1] = (*game)->v_y + ctr[1];
// 			if (mp[0] >= 0 && mp[0] < (*game)->map->h && mp[1] >= 0
// 				&& mp[1] < (*game)->map->w)
// 			{
// 				tile = (*game)->map->grid[mp[0]][mp[1]];
// 				put_relevant_image(game, ctr, mp, tile);
// 			}
// 			ctr[1]++;
// 		}
// 		ctr[0]++;
// 	}
// }

void	reload_map(t_game **game, int prev_x, int prev_y) // from solong
{
	(void)game;
	(void)prev_x;
	(void)prev_y;
	// calculate_viewable_area(game);
	// if ((*game)->map->grid[prev_x][prev_y] == 'C')
	// {
	// 	(*game)->c_count += 1;
	// 	(*game)->map->grid[prev_x][prev_y] = '0';
	// }
	// // render_viewable_map(game);
	// redraw_player(*game);
}

void	set_view_dimensions(t_game **game)
{
	if ((*game)->map->w < WIDTH)
		(*game)->view_w = (*game)->map->w;
	else
		(*game)->view_w = WIDTH;
	if ((*game)->map->h < HEIGHT)
		(*game)->view_h = (*game)->map->h;
	else
		(*game)->view_h = HEIGHT;
}


// void	get_map_edges(t_game **game, char *f_map) // from solong
// {
// 	int		h;
// 	int		w;
// 	int		fd;
// 	char	*line;

// 	h = 0;
// 	w = 0;
// 	if (!f_map)
// 		return ;
// 	fd = open(f_map, O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line != NULL && *line != '\n')
// 	{
// 		w = ft_strlen(line);
// 		if (line[w - 1] != '\n')
// 			w += 1;
// 		h++;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	(*game)->map->h = h;
// 	(*game)->map->w = w;
// 	free(line);
// 	line = NULL;
// 	close(fd);
// }

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	/* 1. Guard against writing outside the image boundaries (Segfault prevention) */
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;

	/* 2. Calculate the exact memory address of the pixel (x, y) */
	/* Formula: start_address + (y * line_length) + (x * bytes_per_pixel) */
	dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));

	/* 3. Cast the address to an unsigned int pointer and set the color */
	*(unsigned int *)dst = color;
}

// void	render_view(t_game **game)
// {
// 	// render_map(game); // old, from solong;
// 	render_raycast(**game); // todo, needs to fix.
// }

t_texture	*select_texture(t_game *game, t_ray *ray)
{
	/* 1. If side == 0, we hit an East or West facing wall (X-side) */
	if (ray->side == 0)
	{
		/* Ray was moving Right -> hit the West face of a block */
		if (ray->ray_dir_x > 0)
			return (&game->tex_west);
		/* Ray was moving Left -> hit the East face of a block */
		return (&game->tex_east);
	}
	/* 2. If side == 1, we hit a North or South facing wall (Y-side) */
	else
	{
		/* Ray was moving Down -> hit the North face of a block */
		if (ray->ray_dir_y > 0)
			return (&game->tex_north);
		/* Ray was moving Up -> hit the South face of a block */
		return (&game->tex_south);
	}
}

int	get_texture_pixel(t_game *game, t_ray *ray, int y, int line_h)
{
	t_texture	*tex;
	int			tex_y;
	double		step;
	double		tex_pos;
	char		*color_ptr;

	/* 1. Pick the correct texture (North, South, East, or West) */
	tex = select_texture(game, ray);

	/* 2. Calculate how many texture pixels to skip for every screen pixel */
	/* We use 1.0 to force double precision */
	step = 1.0 * tex->height / line_h;

	/* 3. Calculate the starting position in the texture */
	/* (y - HEIGHT / 2 + line_h / 2) finds the relative position in the wall */
	tex_pos = (y - HEIGHT / 2 + line_h / 2) * step;
	
	/* 4. Get the integer Y coordinate, masking to prevent out-of-bounds */
	tex_y = (int)tex_pos & (tex->height - 1);

	/* 5. Access the color at (tex_x, tex_y) in the texture's memory */
	/* Formula: addr + (y * line_len + x * bytes_per_pixel) */
	color_ptr = tex->addr + (tex_y * tex->line_len + ray->tex_x * (tex->bpp / 8));
	
	return (*(unsigned int *)color_ptr);
}

