/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 21:18:24 by jotong            #+#    #+#             */
/*   Updated: 2026/04/24 21:23:47 by jotong           ###   ########.fr       */
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
