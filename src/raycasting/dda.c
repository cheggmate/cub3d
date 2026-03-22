/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:04:57 by jotong            #+#    #+#             */
/*   Updated: 2026/03/21 16:33:54 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dda.c: Implementation of the Digital Differential Analyzer algorithm.

#include "cub3d.h"

void    calculate_ray(t_game **game, t_ray *ray, int x)
{
    double camera_x;
    
	camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
    ray->ray_dir_x = (*game)->player.dir_x + (*game)->player.plane_x * camera_x;
    ray->ray_dir_y = (*game)->player.dir_y + (*game)->player.plane_y * camera_x;
    ray->map_x = (int)(*game)->player.pos_x;
    ray->map_y = (int)(*game)->player.pos_y;
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
}

void    perform_dda(t_game **game, t_ray *ray)
{
    int hit = 0;
    while (hit == 0)
    {
        // Jump to next map square in x-direction OR y-direction
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
        // Check if ray has hit a wall
        if ((*game)->map->grid[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}

int    init_ray_dims(t_game **game, t_ray *ray, int x)
{
	double	camera_x;

	/* 1. Camera X is the x-coordinate on the camera plane (-1 to 1) */
	/* 0 is left, WIDTH/2 is center (0), WIDTH is right (1) */
	camera_x = 2 * x / (double)WIDTH - 1;

	/* 2. Ray direction: Player direction + (Plane * CameraX) */
	ray->ray_dir_x = (*game)->player.dir_x + (*game)->player.plane_x * camera_x;
	ray->ray_dir_y = (*game)->player.dir_y + (*game)->player.plane_y * camera_x;

	/* 3. The current square of the map the ray is in */
	ray->map_x = (int)(*game)->player.pos_x;
	ray->map_y = (int)(*game)->player.pos_y;

	/* 4. Delta Dist: distance the ray has to travel to go from 1 x-side 
	   to the next x-side (or y-side to y-side) */
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30; // "Infinity" if ray is parallel to X
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30; // "Infinity" if ray is parallel to Y
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	return (0);
}

void	calculate_wall_dist(t_game *game, t_ray *ray)
{
	(void)game; // Fixes "unused parameter" error
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	
	if (ray->wall_dist < 0.0001)
		ray->wall_dist = 0.0001;

	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	render_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	/* 1. Ceiling */
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(game, x, y, game->floor_colour);
		y++;
	}
	/* 2. Wall */
	while (y < ray->draw_end)
	{
		// Use ray->line_height from the struct
		int color = get_texture_pixel(game, ray, y, ray->line_height);
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
	/* 3. Floor */
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, game->ceiling_colour);
		y++;
	}
}
