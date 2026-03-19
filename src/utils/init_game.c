/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:33:35 by jotong            #+#    #+#             */
/*   Updated: 2026/03/19 17:52:40 by jotong           ###   ########.fr       */
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
	return (0);
}

void	init_game(t_game **game, char *f_map)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!(*game))
		free_and_exit(game, 1, "Failed to alloc mem for game.\n");
	// (*game)->mlx_ptr = mlx_init();	// TODO: uncomment later
	// if (!(*game)->mlx_ptr)
	// 	free_and_exit(game, 1, "Failed to init mlx.\n");
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

void init_grid(t_game **game)
{
    int i;

    // Allocate the array of row pointers
    (*game)->map->grid = ft_calloc((*game)->map->h + 1, sizeof(char *));
    if (!(*game)->map->grid)
        free_and_exit(game, 1, "Failed to allocate grid pointers.\n");

    i = 0;
    while (i < (*game)->map->h)
    {
        (*game)->map->grid[i] = malloc(sizeof(char) * ((*game)->map->w + 1));
        if (!(*game)->map->grid[i])
            free_and_exit(game, 1, "Failed to allocate grid row.\n");
        ft_memset((*game)->map->grid[i], ' ', (*game)->map->w);
        (*game)->map->grid[i][(*game)->map->w] = '\0'; // Null terminate
        i++;
    }
}
