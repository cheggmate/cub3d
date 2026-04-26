/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:03:09 by jotong            #+#    #+#             */
/*   Updated: 2026/04/27 00:13:45 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

int	init_checked_grid(t_game *game, int ***checked)
{
	int	i;

	*checked = ft_calloc(game->map->h, sizeof(int *));
	if (!*checked)
		return (0);
	i = 0;
	while (i < game->map->h)
	{
		(*checked)[i] = ft_calloc(game->map->w, sizeof(int));
		if (!(*checked)[i])
		{
			while (--i >= 0)
				free((*checked)[i]);
			return (free(*checked), 0);
		}
		i++;
	}
	return (1);
}

int	check_tile(int n[2], t_game *game, int **chkd, t_queue *q)
{
	char	c;

	if (n[0] < 0 || n[0] >= game->map->h || n[1] < 0 || n[1] >= game->map->w)
		return (0);
	c = game->map->grid[n[0]][n[1]]; 
	if (c == ' ' || c == '\0')
		return (0);
	if (c == '1' || chkd[n[0]][n[1]])
		return (1);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		chkd[n[0]][n[1]] = 1;
		q->items[q->back++] = (t_pos){n[0], n[1]};
	}
	return (1);
}

int	explore_neighbors(t_pos curr, t_queue *q, t_game *game, int **chkd)
{
    static int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int i;
    int row_with_offset[2];

    i = 0;
    while (i < 4)
    {
        row_with_offset[0] = curr.row + offset[i][0];
        row_with_offset[1] = curr.col + offset[i][1];
        if (!check_tile(row_with_offset, game, chkd, q))
            return (0);
        i++;
    }
    return (1);
}

int run_bfs_from_pos(t_game *game, int start_y, int start_x, int **chkd)
{
    t_queue q;
    t_pos   curr;

    q.front = 0;
    q.back = 0;
    q.items = ft_calloc(game->map->h * game->map->w, sizeof(t_pos));
    if (!q.items)
        return (0);
    chkd[start_y][start_x] = 1;
    q.items[q.back++] = (t_pos){start_y, start_x};
    while (q.front < q.back)
    {
        curr = q.items[q.front++];
        if (!explore_neighbors(curr, &q, game, chkd))
        {
            free(q.items);
            return (0); // Leak found
        }
    }
    free(q.items);
    return (1);
}
