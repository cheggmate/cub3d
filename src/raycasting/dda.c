/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:04:57 by jotong            #+#    #+#             */
/*   Updated: 2026/02/22 10:05:04 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dda.c: Implementation of the Digital Differential Analyzer algorithm.

#include "cub3d.h"

void    calculate_ray(t_data *data, t_ray *ray, int x)
{
    // Calculate ray position and direction
    double camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
    ray->ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
    ray->ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;

    // Current square of the map the ray is in
    ray->map_x = (int)data->player.pos_x;
    ray->map_y = (int)data->player.pos_y;

    // Length of ray from one x or y-side to next x or y-side
    // Avoid division by zero
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
}

void    perform_dda(t_data *data, t_ray *ray)
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
        if (data->map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}
