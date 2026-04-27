/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:13:00 by jotong            #+#    #+#             */
/*   Updated: 2026/04/28 01:13:36 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	render_raycast(t_game *game)
{
	int		x;
	t_ray	ray;

	move_player(game);
	handle_rotation(game);
	x = 0;
	while (x < WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		calculate_ray(game, &ray, x);
		perform_dda(game, &ray); 
		calculate_wall_dist(game, &ray);
		render_vertical_line(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr,
		game->win_ptr, game->img.img_ptr, 0, 0);
	return (0);
}
