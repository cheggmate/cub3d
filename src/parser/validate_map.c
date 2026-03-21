/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:20:51 brow jotong            #+#    #+#             */
/*   Updated: 2026/03/21 16:18:08 brow jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include "cub3d.h"

static int	is_valid_tile(int r, int c, t_game *game, int **checked)
{
	if (r < 0 || c < 0 || r >= game->map->h || c >= game->map->w)
		return (-1);
	if (game->map->grid[r][c] == ' ' || game->map->grid[r][c] == '\0')
		return (-1);
	if (game->map->grid[r][c] == '1' || checked[r][c])
		return (0);
	return (1);
}

static int	explore_neighbors(t_pos curr, t_queue *q, t_game *game, int **chkd)
{
	static int	offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int			i;
	int			nr;
	int			nc;
	int			res;

	i = 0;
	while (i < 4)
	{
		nr = curr.row + offset[i][0];
		nc = curr.col + offset[i][1];
		res = is_valid_tile(nr, nc, game, chkd);
		if (res == -1)
			return (0);
		if (res == 1)
		{
			chkd[nr][nc] = 1;
			q->items[q->back++] = (t_pos){nr, nc};
		}
		i++;
	}
	return (1);
}

// static void	free_checked(int **checked, int height)
// {
// 	int	i;

// 	i = 0;
// 	if (!checked)
// 		return ;
// 	while (i < height)
// 	{
// 		free(checked[i]);
// 		i++;
// 	}
// 	free(checked);
// }

static int	init_checked_grid(t_game *game, int ***checked)
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
			free_checked(*checked, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_map_closed(t_game *game)
{
	t_queue	q;
	int		**checked;

	if (!init_checked_grid(game, &checked))
		return (0);
	q.items = ft_calloc(game->map->h * game->map->w, sizeof(t_pos));
	if (!q.items)
		return (free_checked(checked, game->map->h), 0);
	q.front = 0;
	q.back = 0;
	q.items[q.back++] = (t_pos){(int)game->player.pos_y, (int)game->player.pos_x};
	checked[(int)game->player.pos_y][(int)game->player.pos_x] = 1;
	while (q.front < q.back)
	{
		if (!explore_neighbors(q.items[q.front++], &q, game, checked))
		{
			free(q.items);
			free_checked(checked, game->map->h);
			return (0);
		}
	}
	free(q.items);
	free_checked(checked, game->map->h);
	return (1);
}
