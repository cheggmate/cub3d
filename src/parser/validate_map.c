/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:20:51 by jotong            #+#    #+#             */
/*   Updated: 2026/03/20 16:20:39 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// validate_map.c: Contains the flood-fill logic to ensure the map is closed.

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static int is_valid(int x, int y, t_game *game, int **checked)
{
	// 1. Boundary check: If we step outside the grid dimensions, the map LEAKS
	if (y < 0 || x < 0 || y >= game->map->h || x >= game->map->w)
		return (-1);

	// 2. Void check: If a walkable area is next to a 'space', the map LEAKS
	// Note: using grid[y][x] because y is the row and x is the column
	if (game->map->grid[y][x] == ' ' || game->map->grid[y][x] == '\0')
		return (-1);

	// 3. Wall/Visited check: We stop at walls ('1') or if we've been here before
	if (game->map->grid[y][x] == '1' || checked[y][x])
		return (0);

	return (1); // This is a valid floor/player tile to explore
}

static int explore_neighbors(t_pos *curr, t_queue *q, t_game *game, int **chkd)
{
	// Static directions: Up, Down, Left, Right
	static int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int i = 0;

	while (i < 4)
	{
		int nx = curr->x + dirs[i][0];
		int ny = curr->y + dirs[i][1];
		int res = is_valid(nx, ny, game, chkd);

		if (res == -1) // Found a path to the void!
			return (0);
		if (res == 1)
		{
			chkd[ny][nx] = 1;
			q->q[q->back++] = (t_pos){nx, ny};
		}
		i++;
	}
	return (1);
}

// Helper to safely free the 2D checked array
// static void free_checked(int **checked, int height)
// {
// 	int i = 0;
// 	if (!checked)
// 		return;
// 	while (i < height)
// 	{
// 		free(checked[i]);
// 		i++;
// 	}
// 	free(checked);
// }

int is_map_closed(t_game *game)
{
	t_queue *q;
	int     **checked;
	int     i;
    int     start_x;
	int		start_y;

	// 1. Allocate Queue and Checked Grid
	// Size the queue buffer to handle the worst-case (every tile is a floor)
	q = ft_calloc(1, sizeof(t_queue) + (sizeof(t_pos) * (game->map->h * game->map->w)));
	checked = ft_calloc(game->map->h, sizeof(int *));
	if (!q || !checked)
		return (free(q), free(checked), -1);
	i = 0;
	while (i < game->map->h)
	{
		checked[i] = ft_calloc(game->map->w, sizeof(int));
		if (!checked[i++])
			return (free_checked(checked, i - 1), free(q), 0);
	}
	start_x = (int)game->player.pos_x;
	start_y = (int)game->player.pos_y;
	q->q[q->back++] = (t_pos){start_x, start_y};
	checked[start_y][start_x] = 1;
	while (q->front < q->back)
	{
		t_pos curr = q->q[q->front++];
		if (!explore_neighbors(&curr, q, game, checked))
		{
			free_checked(checked, game->map->h);
			free(q);
			return (-1);
		}
	}
	free_checked(checked, game->map->h);
	free(q);
	return (0);
}
