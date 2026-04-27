/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 21:18:24 by jotong            #+#    #+#             */
/*   Updated: 2026/04/28 01:15:28 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->delta_dist_y;
	}
}

void	set_ray(t_game *game, t_ray **ray)
{
	if ((*ray)->ray_dir_x < 0)
	{
		(*ray)->step_x = -1;
		(*ray)->side_dist_x = (game->player.pos_x - (*ray)->map_x)
			* (*ray)->delta_dist_x;
	}
	else
	{
		(*ray)->step_x = 1;
		(*ray)->side_dist_x = ((*ray)->map_x + 1.0 - game->player.pos_x)
			* (*ray)->delta_dist_x;
	}
	if ((*ray)->ray_dir_y < 0)
	{
		(*ray)->step_y = -1;
		(*ray)->side_dist_y = (game->player.pos_y - (*ray)->map_y)
			* (*ray)->delta_dist_y;
	}
	else
	{
		(*ray)->step_y = 1;
		(*ray)->side_dist_y = ((*ray)->map_y + 1.0 - game->player.pos_y)
			* (*ray)->delta_dist_y;
	}
}

void	render_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	color ;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(game, x, y, game->ceiling_colour);
		y++;
	}
	while (y < ray->draw_end)
	{
		color = get_texture_pixel(game, ray, y, ray->line_height);
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, game->floor_colour);
		y++;
	}
}

static void	step_next_tile(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	int		hit;
	char	cell;

	hit = 0;
	while (hit == 0)
	{
		step_next_tile(ray);
		if (ray->map_y < 0 || ray->map_x < 0
			|| ray->map_y >= game->map->h || ray->map_x >= game->map->w)
		{
			hit = 1;
			break ;
		}
		cell = game->map->grid[ray->map_y][ray->map_x];
		if (cell == '1' || cell == ' ' || cell == '\0')
			hit = 1;
	}
}
