/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:03:09 by jotong            #+#    #+#             */
/*   Updated: 2026/03/23 15:17:19 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

// static int	is_valid_tile(int r, int c, t_game *game, int **checked)
// {
// 	if (r < 0 || c < 0 || r >= game->map->h || c >= game->map->w)
// 		return (-1);
// 	if (game->map->grid[r][c] == ' ' || game->map->grid[r][c] == '\0')
// 		return (-2);
// 	if (game->map->grid[r][c] == '1' || checked[r][c])
// 		return (0);
// 	return (1);
// }

// /*
// ** Explores the 4 cardinal neighbors. If a walkable tile 
// ** touches a -1 or -2 result, it means the map is open.
// */
// static int	explore_neighbors(t_pos curr, t_queue *q, t_game *game, int **chkd)
// {
// 	static int	offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// 	int			i;
// 	int			nr;
// 	int			nc;
// 	int			res;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		nr = curr.row + offset[i][0];
// 		nc = curr.col + offset[i][1];
// 		res = is_valid_tile(nr, nc, game, chkd);
// 		if (res == -1 || res == -2)
// 			return (0);
// 		if (res == 1)
// 		{
// 			chkd[nr][nc] = 1;
// 			q->items[q->back++] = (t_pos){nr, nc};
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// static int	init_checked_grid(t_game *game, int ***checked)
// {
// 	int	i;

// 	*checked = ft_calloc(game->map->h, sizeof(int *));
// 	if (!*checked)
// 		return (0);
// 	i = 0;
// 	while (i < game->map->h)
// 	{
// 		(*checked)[i] = ft_calloc(game->map->w, sizeof(int));
// 		if (!(*checked)[i])
// 		{
// 			while (--i >= 0)
// 				free((*checked)[i]);
// 			return (free(*checked), 0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// static void	cleanup_validation(t_queue *q, int **checked, int height)
// {
// 	int	i;

// 	i = 0;
// 	if (q->items)
// 		free(q->items);
// 	if (checked)
// 	{
// 		while (i < height)
// 			free(checked[i++]);
// 		free(checked);
// 	}
// }

// int	is_map_closed(t_game *game)
// {
// 	t_queue	q;
// 	int		**checked;

// 	if (!init_checked_grid(game, &checked))
// 		return (0);
// 	q.items = ft_calloc(game->map->h * game->map->w, sizeof(t_pos));
// 	if (!q.items)
// 		return (cleanup_validation(&q, checked, game->map->h), 0);
// 	q.front = 0;
// 	q.back = 0;
// 	q.items[q.back++] = (t_pos){(int)game->player.pos_y, (int)game->player.pos_x};
// 	checked[(int)game->player.pos_y][(int)game->player.pos_x] = 1;
// 	while (q.front < q.back)
// 	{
// 		if (!explore_neighbors(q.items[q.front++], &q, game, checked))
// 		{
// 			cleanup_validation(&q, checked, game->map->h);
// 			return (0);
// 		}
// 	}
// 	cleanup_validation(&q, checked, game->map->h);
// 	return (1);
// }

static int	is_floor(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

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

static int	check_tile(int nr, int nc, t_game *game, int **chkd, t_queue *q)
{
	char	cell;

	if (nr < 0 || nc < 0 || nr >= game->map->h || nc >= game->map->w)
	{
		printf("FAIL: out of bounds at [%d][%d] (map is %dx%d)\n",
			nr, nc, game->map->h, game->map->w);
		return (0);
	}
	cell = game->map->grid[nr][nc];
	if (cell == ' ' || cell == '\0')
	{
		printf("FAIL: space/null at [%d][%d] (neighbor of a floor tile)\n", nr, nc);
		printf("      grid[%d] = '%s'\n", nr, game->map->grid[nr]);
		return (0);
	}
	if (cell == '1' || chkd[nr][nc])
		return (1);
	if (is_floor(cell))
	{
		chkd[nr][nc] = 1;
		q->items[q->back++] = (t_pos){nr, nc};
	}
	return (1);
}

static int	explore_neighbors(t_pos curr, t_queue *q, t_game *game, int **chkd)
{
	static int	offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (!check_tile(curr.row + offset[i][0], curr.col + offset[i][1],
				game, chkd, q))
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

	printf("=== is_map_closed ===\n");
	printf("player pos: row=%d col=%d\n",
		(int)game->player.pos_y, (int)game->player.pos_x);
	printf("map dimensions: h=%d w=%d\n", game->map->h, game->map->w);
	printf("=== grid as stored ===\n");
	int i = 0;
	while (i < game->map->h)
	{
		printf("row[%02d] len=%-3d |%s|\n",
			i, (int)ft_strlen(game->map->grid[i]), game->map->grid[i]);
		i++;
	}
	printf("======================\n");
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
		{
			cleanup_validation(&q, checked, game->map->h);
			printf("=== map is NOT closed ===\n");
			return (0);
		}
	}
	cleanup_validation(&q, checked, game->map->h);
	printf("=== map IS closed ===\n");
	return (1);
}
