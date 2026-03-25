/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:23:30 by jotong            #+#    #+#             */
/*   Updated: 2026/03/25 19:01:46 by jotong           ###   ########.fr       */
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

	width = ((*game)->view_w);
	height = ((*game)->view_h);
	(*game)->win_ptr = mlx_new_window(mlx, width, height, "cub3d");
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

int	handle_close(void *game_in)
{
	t_game	*game;

	game = (t_game *)game_in;
	close_window(game);
	return (0);
}

void	reload_map(t_game **game, int prev_x, int prev_y)
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

void	my_mlx_pixel_put(t_game *game, int x, int y, int colour)
{
	char	*dst;

	/* 1. Guard against writing outside the image boundaries (Segfault prevention) */
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;

	if (!game->img.addr)
		return ;

	/* 2. Calculate the exact memory address of the pixel (x, y) */
	/* Formula: start_address + (y * line_length) + (x * bytes_per_pixel) */
	dst = game->img.addr + (y * game->img.line_length + x * (game->img.bpp / 8));

	/* 3. Cast the address to an unsigned int pointer and set the colour */
	*(unsigned int *)dst = colour;
}

t_texture   *select_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0) // Hits Vertical Wall (East/West)
    {
        if (ray->ray_dir_x > 0)
            return (&game->textures[3]); // WE (West face)
        return (&game->textures[2]);      // EA (East face)
    }
    else // Hits Horizontal Wall (North/South)
    {
        if (ray->ray_dir_y < 0)
            return (&game->textures[1]); // SO (South face)
        return (&game->textures[0]);      // NO (North face)
    }
}

static unsigned int	add_shade(char *colour_ptr, t_ray *ray)
{
	unsigned int	colour;
	double			shadow;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	colour = *(unsigned int *)colour_ptr;
	if (ray->side == 1)
    colour = (colour >> 1) & 8355711; // Darken the RGB bits

	// distance shading
	shadow = 1.0 / (1.0 + ray->wall_dist * 0.05); // Adjust 0.05 for intensity

    r = (colour >> 16) & 0xFF;
    g = (colour >> 8) & 0xFF;
    b = colour & 0xFF;

    r = (unsigned int)(r * shadow);
    g = (unsigned int)(g * shadow);
    b = (unsigned int)(b * shadow);

    return ((r << 16) | (g << 8) | b);
}

int	get_texture_pixel(t_game *game, t_ray *ray, int y, int line_h)
{
	t_texture	*tex;
	int			tex_y;
	double		step;
	double		tex_pos;
	char		*colour_ptr;

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

	/* 5. Access the colour at (tex_x, tex_y) in the texture's memory */
	/* Formula: addr + (y * line_len + x * bytes_per_pixel) */
	colour_ptr = tex->addr + (tex_y * tex->line_len + ray->tex_x * (tex->bpp / 8));
	
	return (add_shade(colour_ptr, ray));
}

