/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:03:09 by jotong            #+#    #+#             */
/*   Updated: 2026/04/26 22:35:45 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

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
			while (--i >= 0)
				free((*checked)[i]);
			return (free(*checked), 0);
		}
		i++;
	}
	return (1);
}

static void	cleanup_validation(t_queue *q, int **checked, int height)
{
	int	i;

	i = 0;
	if (q->items)
		free(q->items);
	if (checked)
	{
		while (i < height)
			free(checked[i++]);
		free(checked);
	}
}

static int	check_tile(int *n, t_game *game, int **chkd, t_queue *q)
{
	char	c;

	if (n[0] < 0 || n[1] < 0 || n[0] >= game->map->h || n[1] >= game->map->w)
	{
		printf("FAIL: out of bounds at [%d][%d] (map is %dx%d)\n",
			n[0], n[1], game->map->h, game->map->w);
		return (0);
	}
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

static int	explore_neighbors(t_pos curr, t_queue *q, t_game *game, int **chkd)
{
	static int	offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int			i;
	int			row_with_offset[2];

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

int	is_map_closed(t_game *game)
{
	t_queue	q;
	int		**checked;
	int		start_r;
	int		start_c;

	if (!init_checked_grid(game, &checked))
		return (0);
	q.items = ft_calloc(game->map->h * game->map->w, sizeof(t_pos));
	if (!q.items)
		return (cleanup_validation(&q, checked, game->map->h), 0);
	q.front = 0;
	q.back = 0;
	start_r = (int)game->player.pos_y;
	start_c = (int)game->player.pos_x;
	checked[start_r][start_c] = 1;
	q.items[q.back++] = (t_pos){start_r, start_c};
	while (q.front < q.back)
	{
		if (!explore_neighbors(q.items[q.front++], &q, game, checked))
			return (cleanup_validation(&q, checked, game->map->h), 0);
	}
	cleanup_validation(&q, checked, game->map->h);
	return (1);
}
