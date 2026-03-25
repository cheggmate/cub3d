/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:13:00 by jotong            #+#    #+#             */
/*   Updated: 2026/03/25 18:40:25 by jotong           ###   ########.fr       */
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
	move_player(&game);

	while (x < WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		// // 1. Calculate ray position and direction
		// init_ray_dims(&game, &ray, x);
		// 2. Calculate step and initial sideDist
		calculate_ray(game, &ray, x);
		// 3. Perform DDA to find the wall
		perform_dda(&game, &ray);

		// FORCE DISTANCE TEST - REMOVE LATER
		// ray.wall_dist = 5.0; 
		// ray.side = 0;
		
		// 4. Calculate distance projected on camera direction
		calculate_wall_dist(game, &ray);
		// 5. Draw the vertical line (Ceiling, Wall Texture, Floor)
		render_vertical_line(game, &ray, x);
		x++;
	}
	int y;
	y = 0;
	while (y < HEIGHT)
    {
        if (y < HEIGHT / 2)
            my_mlx_pixel_put(game, x, y, 0x0000FF); // Blue Ceiling
        else
            my_mlx_pixel_put(game, x, y, 0x555555); // Grey Floor
        y++;
    }
	// Draw a small red square in the dead center of the screen
	// my_mlx_pixel_put(game, WIDTH / 2, HEIGHT / 2, 0xFF0000);
	// my_mlx_pixel_put(game, WIDTH / 2 + 1, HEIGHT / 2, 0xFF0000);
	// my_mlx_pixel_put(game, WIDTH / 2, HEIGHT / 2 + 1, 0xFF0000);
	// my_mlx_pixel_put(game, WIDTH / 2 + 1, HEIGHT / 2 + 1, 0xFF0000);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
	return (0);
}
