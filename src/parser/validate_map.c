/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:20:51 by jotong            #+#    #+#             */
/*   Updated: 2026/02/23 15:52:13 by jotong           ###   ########.fr       */
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
    if (x < 0 || y < 0 || x >= game->map->h || y >= game->map->w) // map not enclosed
        return (-1); //  error code for "leaked"
    if (game->map->grid[x][y] == ' ') // spaces
        return (-1);
    if (game->map->grid[x][y] == '1' || checked[x][y]) // already checked
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
        if (!explore_neighbors(&curr, &q, game, checked)) // found a leak 
        {
			free_and_exit(game, 1, "Map is not enclosed by walls.");
            return (0); // Map is INVALID
        }
    }
	free_checked(checked, game->map->h);
    return (1);
}
