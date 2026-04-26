/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:03:09 by jotong            #+#    #+#             */
/*   Updated: 2026/04/27 00:13:10 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"


static int	process_map_tile(t_game *game, int y, int x, int **chkd)
{
	char	c;

	c = game->map->grid[y][x];
	if ((c == '0' || ft_strchr("NSEW", c)) && !chkd[y][x])
	{
		if (!run_bfs_from_pos(game, y, x, chkd))
			return (0);
	}
	return (1);
}

int	is_map_closed(t_game *game)
{
	int	**chkd;
	int	y;
	int	x;

	if (!init_checked_grid(game, &chkd))
		return (0);
	y = 0;
	while (y < game->map->h)
	{
		x = 0;
		while (x < game->map->w)
		{
			if (!process_map_tile(game, y, x, chkd))
			{
				free_checked(chkd, game->map->h);
				return (0);
			}
			x++;
		}
		y++;
	}
	free_checked(chkd, game->map->h);
	return (1);
}
