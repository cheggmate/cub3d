/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 08:15:32 by jotong            #+#    #+#             */
/*   Updated: 2026/03/17 14:41:07 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static int is_valid(int x, int y, t_game **game, int **checked)
{
    // 1. Check if we are touching the actual array boundaries
    if (x < 0 || y < 0 || x >= (*game)->map->h || y >= (*game)->map->w)
        return (-1); // LEAK! Touched the edge of the world

    // 2. Check if we hit a space (the void)
    if ((*game)->map->grid[x][y] == ' ')
        return (-1); // LEAK! Walkable area is next to a hole

    // 3. If it's a wall, it's a safe boundary (don't queue it, but don't leak)
    if ((*game)->map->grid[x][y] == '1')
        return (0);

    // 4. If we've already checked this floor tile, ignore it
    if (checked[x][y])
        return (0);

    // 5. It's a valid, unvisited floor tile (0, N, S, E, or W)
    return (1);
}

static int queue_if_valid(t_pos *curr, t_queue *q, t_game **game, int **chkd)
{
    int i;
    int next_x;
    int next_y;
    int status;

    i = 0;
    while (i < 4)
    {
        next_x = curr->x + q->dir[i][0];
        next_y = curr->y + q->dir[i][1];
        
        status = is_valid(next_x, next_y, game, chkd);
        if (status == -1)
            return (0); // Return "Failure" to the caller
        if (status == 1)
        {
            chkd[next_x][next_y] = 1;
            q->q[q->back++] = (t_pos){next_x, next_y};
        }
        i++;
    }
    return (1); // All neighbors are safe or walls
}

// static void	init_vals(t_queue *q, int **checked, t_game **game)
// {
// 	int	i;

// 	i = -1;
// 	q->dir = ft_calloc(4, sizeof(int *));
// 	if (!q->dir)
// 		free_and_exit(game, 1, "Failed to allocate memory.\n");
// 	while (++i < 4)
// 		q->dir[i] = ft_calloc(2, sizeof(int));
// 	i = -1;
// 	q->dir[0][0] = 0;
// 	q->dir[0][1] = 1;
// 	q->dir[1][0] = 1;
// 	q->dir[1][1] = 0;
// 	q->dir[2][0] = -1;
// 	q->dir[2][1] = 0;
// 	q->dir[3][0] = 0;
// 	q->dir[3][1] = -1;
// 	while (++i < (*game)->map->h)
// 	{
// 		checked[i] = ft_calloc((*game)->map->w, sizeof(int));
// 		if (!checked[i])
// 			free_and_exit(game, 1, "Failed to allocate memory\n");
// 	}
// 	q->front = 0;
// 	q->back = 0;
// }

int	path_check(t_game **game)
{
	t_queue	*q;
	int		**checked;
	t_pos	curr;

	q = (t_queue *)ft_calloc(1, sizeof(t_queue));
	checked = ft_calloc((*game)->map->h, sizeof(int *));
	// Set starting point (Cast doubles to int for grid access)
    int start_x = (int)(*game)->player.pos_x;
    int start_y = (int)(*game)->player.pos_y;
    
    q->q[q->back++] = (t_pos){start_x, start_y};
    checked[start_x][start_y] = 1;

    while (q->front < q->back)
    {
        curr = q->q[q->front++];
        if (!queue_if_valid(&curr, q, game, checked))
        {
            return (free(q), free(checked), 0); // Map is INVALID (it leaked)
        }
    }
    return (free(q), free(checked), 1); // Map is VALID (fully enclosed)
}
