/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 08:15:32 by jotong            #+#    #+#             */
/*   Updated: 2026/03/19 17:31:33 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

#include "cub3d.h"

static int is_valid(int x, int y, t_game **game, int **checked)
{
    // 1. Boundary check: Are we outside the allocated grid?
    if (x < 0 || y < 0 || x >= (*game)->map->h || y >= (*game)->map->w)
        return (-1);

    // 2. Void check: Are we walking into a 'space' that should be a wall?
    if ((*game)->map->grid[x][y] == ' ' || (*game)->map->grid[x][y] == '\0')
        return (-1);

    // 3. Wall check: '1' is a safe boundary, but we don't walk through it
    if ((*game)->map->grid[x][y] == '1')
        return (0);

    // 4. Visit check: Don't process the same tile twice
    if (checked[x][y])
        return (0);

    return (1); // Valid floor/player start tile
}

static int queue_if_valid(t_pos *curr, t_queue *q, t_game **game, int **chkd)
{
    // Static directions: Up, Down, Left, Right
    static int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int i = 0;

    while (i < 4)
    {
        int nx = curr->x + dir[i][0];
        int ny = curr->y + dir[i][1];
        int status = is_valid(nx, ny, game, chkd);

        if (status == -1)
            return (0); // LEAK DETECTED
        if (status == 1)
        {
            chkd[nx][ny] = 1;
            q->q[q->back++] = (t_pos){nx, ny};
        }
        i++;
    }
    return (1);
}

int path_check(t_game **game)
{
    t_queue *q;
    int     **checked;
    int     i;
    int     result = 1;

    // 1. Allocate BFS Queue and Checked Grid
    // Size of queue should be at least (width * height)
    q = ft_calloc(1, sizeof(t_queue) + (sizeof(t_pos) * ((*game)->map->h * (*game)->map->w)));
    checked = ft_calloc((*game)->map->h, sizeof(int *));
    if (!q || !checked)
        return (free(q), free(checked), 0);

    i = -1;
    while (++i < (*game)->map->h)
    {
        checked[i] = ft_calloc((*game)->map->w, sizeof(int));
        if (!checked[i])
            return (free_checked(checked, i), free(q), 0);
    }

    // 2. Start BFS from player position
    int start_x = (int)(*game)->player.pos_y; // Usually grid[y][x]
    int start_y = (int)(*game)->player.pos_x;
    
    q->q[q->back++] = (t_pos){start_x, start_y};
    checked[start_x][start_y] = 1;

    while (q->front < q->back)
    {
        t_pos curr = q->q[q->front++];
        if (!queue_if_valid(&curr, q, game, checked))
        {
            result = 0; // Map is open!
            break;
        }
    }

    // 3. Cleanup and Return
    free_checked(checked, (*game)->map->h);
    free(q);
    return (result);
}