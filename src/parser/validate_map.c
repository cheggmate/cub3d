/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:20:51 by jotong            #+#    #+#             */
/*   Updated: 2026/02/22 16:44:20 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// validate_map.c: Contains the flood-fill logic to ensure the map is closed.

#include "cub3d.h"
#include "libft.h"
#ifdef __APPLE__
# include "minilibx_opengl_20191021/mlx.h"
#elif __linux__
# include "minilibx-linux/mlx.h"
#endif

static int is_valid(int x, int y, t_game *game, int **checked)
{
    // 1. If we are OUTSIDE the map boundaries, the map is NOT closed.
    if (x < 0 || y < 0 || x >= game->map->h || y >= game->map->w)
        return (-1); // Special error code for "leaked"

    // 2. If we hit a space, it's a hole in the map.
    if (game->map->grid[x][y] == ' ')
        return (-1);

    // 3. If it's a wall or already checked, don't go there.
    if (game->map->grid[x][y] == '1' || checked[x][y])
        return (0);

    return (1); // Valid floor space to explore
}

static int explore_neighbors(t_pos *curr, t_queue *q, t_game *game, int **chkd)
{
    int i = 0;
    int next_x, next_y;
    int res;

    while (i < 4)
    {
        next_x = curr->x + q->dir[i][0];
        next_y = curr->y + q->dir[i][1];
        res = is_valid(next_x, next_y, game, chkd);
        
        if (res == -1) // Map is open!
            return (0);
        if (res == 1)
        {
            chkd[next_x][next_y] = 1;
            q->q[q->back++] = (t_pos){next_x, next_y};
        }
        i++;
    }
    return (1);
}

int is_map_closed(t_game *game)
{
    t_queue q;
    int     **checked;
    t_pos   curr;

    q = (t_queue *)ft_calloc(1, sizeof(t_queue));
	checked = ft_calloc(1, sizeof(int *) * (*game)->map->h);
    // Start BFS from player position
    q.q[q.back++] = (t_pos){game->p_x, game->p_y};
    checked[game->p_x][game->p_y] = 1;

    while (q.front < q.back)
    {
        curr = q.q[q.front++];
        
        // If explore_neighbors returns 0, it found a leak to the outside
        if (!explore_neighbors(&curr, &q, game, checked))
        {
			free_and_exit(game, 1, "Map is not enclosed by walls.");
            // Free memory before returning!
            return (0); // Map is INVALID
        }
    }
	free_checked(checked, game->map->h);
    return (1);
}
