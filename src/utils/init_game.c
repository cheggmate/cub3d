/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:33:35 by jotong            #+#    #+#             */
/*   Updated: 2026/02/28 15:38:35 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	init_game(t_pool *mem_p, t_game **game, char *f_map)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!(*game))
		free_and_exit(game, 1, "Failed to alloc mem for game.\n");
	// (*game)->mem_p = mem_p;
	(*game)->mlx = mlx_init();
	if (!(*game)->mlx)
		free_and_exit(game, 1, "Failed to init mlx.\n");
	floor_color = -1;
	ceiling_color = -1;
	(*game)->mp = f_map;
	(*game)->v_x = 0;
	(*game)->v_y = 0;
	(*game)->view_w = 0;
	(*game)->view_h = 0;
	(*game)->map = ft_calloc(1, sizeof(t_map));
	if (!(*game)->map)
		free_and_exit(game, 1, "Invalid map.\n");
	initialise_map_values(game, f_map);
}

