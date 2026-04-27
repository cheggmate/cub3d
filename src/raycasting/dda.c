/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:04:57 by jotong            #+#    #+#             */
/*   Updated: 2026/04/28 01:15:43 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	set_ray(game, &ray);
}

int	init_ray_dims(t_game **game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = (*game)->player.dir_x + (*game)->player.plane_x * camera_x;
	ray->ray_dir_y = (*game)->player.dir_y + (*game)->player.plane_y * camera_x;
	ray->map_x = (int)(*game)->player.pos_x;
	ray->map_y = (int)(*game)->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	return (0);
}

static void	calculate_wall_dist_in_ray(t_ray **ray)
{
	if ((*ray)->side == 0)
		(*ray)->wall_dist = ((*ray)->side_dist_x - (*ray)->delta_dist_x);
	else
		(*ray)->wall_dist = ((*ray)->side_dist_y - (*ray)->delta_dist_y);
	if ((*ray)->wall_dist <= 0)
		(*ray)->wall_dist = 0.1;
}

void	calculate_wall_dist(t_game *game, t_ray *ray)
{
	double		wall_x;
	t_texture	*tex;

	calculate_wall_dist_in_ray(&ray);
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	tex = select_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
}
