/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:33:35 by jotong            #+#    #+#             */
/*   Updated: 2026/03/17 15:08:27 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static int	initialise_map_values(t_game **game, char *f_map)
{
	(void)f_map;
	(*game)->map = ft_calloc(1, sizeof(t_map));
	if (!(*game)->map)
		return (-1);
	// get_map_edges(game, f_map);
	// (*game)->map->start = 0;
	// (*game)->map->p_start_x = 0;
	// (*game)->map->p_start_y = 0;
	return (0);
}

void	init_game(t_game **game, char *f_map)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!(*game))
		free_and_exit(game, 1, "Failed to alloc mem for game.\n");
	(*game)->mlx_ptr = mlx_init();
	if (!(*game)->mlx_ptr)
		free_and_exit(game, 1, "Failed to init mlx.\n");
	(*game)->floor_colour = -1;
	(*game)->ceiling_colour = -1;
	(*game)->mp = f_map;
	// (*game)->v_x = 0;
	// (*game)->v_y = 0;
	(*game)->view_w = 0;
	(*game)->view_h = 0;
	if (initialise_map_values(game, f_map) == -1)
		free_and_exit(game, 1, "Invalid map.\n");
}

void	init_grid(char *f_map, t_game **game)
{
	int		i;

	i = 0;
	(*game)->map->fd = open(f_map, O_RDONLY);
	(*game)->map->grid = ft_calloc(((*game)->map->h + 1), sizeof(char *));
	if (!(*game)->map->grid)
		free_and_exit(game, 1, "Failed to alloc mem for grid.\n");
	while (i < (*game)->map->h)
	{
		(*game)->map->grid[i] = ft_calloc(((*game)->map->w + 1), sizeof(char));
		if (!((*game)->map->grid[i]))
			free_and_exit(game, 1, "Failed to alloc mem for grid.\n");
		i++;
	}
}
