/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:33:35 by jotong            #+#    #+#             */
/*   Updated: 2026/02/18 16:35:02 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	init_game(t_pool *mem_p, t_game **game, char *f_map)
{
	*game = alloc_mem(mem_p, sizeof(t_game));
	if (!(*game))
		free_and_exit(mem_p, game, 1, "Failed to alloc mem for game.\n");
	(*game)->mem_p = mem_p;
	(*game)->mlx = mlx_init();
	if (!(*game)->mlx)
		free_and_exit(mem_p, game, 1, "Failed to init mlx.\n");
	(*game)->c_count = 0;
	(*game)->mp = f_map;
	(*game)->n_mvmts = 0;
	(*game)->v_x = 0;
	(*game)->v_y = 0;
	(*game)->view_w = 0;
	(*game)->view_h = 0;
	(*game)->won = 0;
	(*game)->map = alloc_mem(mem_p, sizeof(t_map));
	if (!(*game)->map)
		free_and_exit(mem_p, game, 1, "Map is not valid / invalid map.\n");
	initialise_map_values(game, f_map);
}