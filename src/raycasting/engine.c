/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:13:00 by jotong            #+#    #+#             */
/*   Updated: 2026/03/24 00:31:24 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// engine.c: The main game loop (mlx_loop_hook).
#include "cub3d.h"
#include "mlx.h"

int	render_raycast(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		// 1. Calculate ray position and direction
		init_ray_dims(&game, &ray, x);
		// 2. Calculate step and initial sideDist
		calculate_ray(&game, &ray, x);
		// 3. Perform DDA to find the wall
		perform_dda(&game, &ray);
		// 4. Calculate distance projected on camera direction
		calculate_wall_dist(game, &ray);
		// 5. Draw the vertical line (Ceiling, Wall Texture, Floor)
		render_vertical_line(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
	return (0);
}
