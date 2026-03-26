/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:04:57 by jotong            #+#    #+#             */
/*   Updated: 2026/03/27 01:04:07 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dda.c: Implementation of the Digital Differential Analyzer algorithm.

#include "cub3d.h"

void init_dda(t_game *game, t_ray *ray)
{
    // Calculate step and initial sideDist
    if (ray->ray_dir_x < 0) {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
    } else {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0) {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
    } else {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
    }
}

void    calculate_ray(t_game *game, t_ray *ray, int x)
{
    double camera_x;

    camera_x = 2 * x / (double)WIDTH - 1;
    ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
    ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
    ray->map_x = (int)game->player.pos_x;
    ray->map_y = (int)game->player.pos_y;
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
    if (ray->ray_dir_x < 0) {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
    } else {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0) {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
    } else {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
    }
}

void    perform_dda(t_game **game, t_ray *ray)
{
    char	cell;

    int hit = 0;
    while (hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y) {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        } else {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (ray->map_y < 0 || ray->map_x < 0 || 
            ray->map_y >= (*game)->map->h || ray->map_x >= (*game)->map->w)
            break;
		cell = (*game)->map->grid[ray->map_y][ray->map_x];
        if (cell == '1' || cell == ' ' || cell == '\0')
            hit = 1;
		fflush(stdout);
    }
}

int    init_ray_dims(t_game **game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = (*game)->player.dir_x + (*game)->player.plane_x * camera_x;
	ray->ray_dir_y = (*game)->player.dir_y + (*game)->player.plane_y * camera_x;
	ray->map_x = (int)(*game)->player.pos_x;
	ray->map_y = (int)(*game)->player.pos_y;
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

void calculate_wall_dist(t_game *game, t_ray *ray)
{
	(void)game;
	double	wall_x;
    if (ray->side == 0)
        ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);

    // IMPORTANT: Protection against division by zero or near-zero
    if (ray->wall_dist <= 0)
        ray->wall_dist = 0.1;

    ray->line_height = (int)(HEIGHT / ray->wall_dist);
    
    // If line_height is bigger than the screen, CAP IT for the loop
    if (ray->line_height > 5000) 
        ray->line_height = 5000;
    // Calculate where to start and end drawing the line
    ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_start < 0) 
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	
	
	if (ray->side == 0)
	    wall_x = game->player.pos_y + ray->wall_dist * ray->ray_dir_y;
	else
	    wall_x = game->player.pos_x + ray->wall_dist * ray->ray_dir_x;
	
	
	wall_x -= floor(wall_x);

	// Assuming your texture width is 64

	// 1. Where on the wall did the ray hit? (0.0 to 1.0)
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->wall_dist * ray->ray_dir_x;

	// 2. Get the fractional part (0.5 means center of the tile)
	wall_x -= floor(wall_x);

	// 3. Map it to your texture width (e.g., 64)
	ray->tex_x = (int)(wall_x * (double)64); // Replace 64 with your actual tex->width

	// 4. Flip to prevent mirroring
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
}

void	render_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	y;
	int color ;

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
