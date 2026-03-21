/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 08:15:32 by jotong            #+#    #+#             */
/*   Updated: 2026/03/21 16:44:05 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

// static int is_valid(int x, int y, t_game **game, int **checked)
// {
//     // 1. Boundary check: Are we outside the allocated grid?
//     if (x < 0 || y < 0 || x >= (*game)->map->h || y >= (*game)->map->w)
//         return (-1);
//     // check for walking into walls
//     if ((*game)->map->grid[x][y] == ' ' || (*game)->map->grid[x][y] == '\0')
//         return (-1);
//     // check for existence of walls
//     if ((*game)->map->grid[x][y] == '1')
//         return (0);
//     // visit check (only go to each tile once)
//     if (checked[x][y])
//         return (0);
//     return (1); // Valid floor/player start tile
// }

// static void	init_dirs(int (*dir)[2])
// {
// 	dir[0][0] = -1;
// 	dir[0][1] = 0;
// 	dir[1][0] = 1;
// 	dir[1][1] = 0;
// 	dir[2][0] = 0;
// 	dir[2][1] = -1;
// 	dir[3][0] = 1;
// 	dir[3][1] = 0;
// }

// static int queue_if_valid(t_pos *curr, t_queue *q, t_game **game, int **chkd)
// {
//     // directions: Up, Down, Left, Right
//     int dir[4][2];
//     int i = 0;

//     init_dirs(dir);
//     while (i < 4)
//     {
//         int nx = curr-> + dir[i][0];
//         int ny = curr->y + dir[i][1];
//         int status = is_valid(nx, ny, game, chkd);

//         if (status == -1)
//             return (0); // LEAK DETECTED
//         if (status == 1)
//         {
//             chkd[nx][ny] = 1;
//             q->q[q->back++] = (t_pos){nx, ny};
//         }
//         i++;
//     }
//     return (1);
// }

// int path_check(t_game **game)
// {
//     t_queue *q;
//     int     **checked;
//     int     i;
//     int     result = 1;

//     q = ft_calloc(1, sizeof(t_queue) + (sizeof(t_pos) * ((*game)->map->h * (*game)->map->w)));
//     checked = ft_calloc((*game)->map->h, sizeof(int *));
//     if (!q || !checked)
//         return (free(q), free(checked), 0);

//     i = -1;
//     while (++i < (*game)->map->h)
//     {
//         checked[i] = ft_calloc((*game)->map->w, sizeof(int));
//         if (!checked[i])
//             return (free_checked(checked, i), free(q), 0);
//     }
//     int start_x = (int)(*game)->player.pos_y;
//     int start_y = (int)(*game)->player.pos_x;
    
//     q->items[q->back++] = (t_pos){start_x, start_y};
//     checked[start_x][start_y] = 1;

//     while (q->front < q->back)
//     {
//         t_pos curr = q->q[q->front++];
//         if (!queue_if_valid(&curr, q, game, checked))
//         {
//             result = 0; // Map is open
//             break;
//         }
//     }
//     free_checked(checked, (*game)->map->h);
//     free(q);
//     return (result);
// }