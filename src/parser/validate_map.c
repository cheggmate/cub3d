/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:20:51 by jotong            #+#    #+#             */
/*   Updated: 2026/02/18 16:33:16 by jotong           ###   ########.fr       */
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


static int	is_valid(int x, int y, t_game **game, int **checked)
{
	return (x >= 0 && y >= 0 && x < (*game)->map->h && y < (*game)->map->w
		&& (*game)->map->grid[x][y] != '1' && !checked[x][y]);
}

static void	queue_if_valid(t_pos *curr, t_queue *q, t_game **game, int **chkd)
{
	int	i;
	int	next_x;
	int	next_y;

	i = 0;
	next_x = 0;
	next_y = 0;
	while (i < 4)
	{
		next_x = curr->x + q->dir[i][0];
		next_y = curr->y + q->dir[i][1];
		if (is_valid(next_x, next_y, game, chkd))
		{
			chkd[next_x][next_y] = 1;
			q->q[q->back++] = (t_pos){next_x, next_y};
		}
		i++;
	}
}

static void	init_vals(t_queue *q, int **checked, t_game **game, t_pool *mem_p)
{
	int	i;

	i = -1;
	q->dir = alloc_mem(mem_p, 4 * sizeof(int *));
	if (!q->dir)
		free_and_exit(mem_p, game, 1, "Failed to allocate memory.\n");
	while (++i < 4)
		q->dir[i] = alloc_mem(mem_p, 2 * sizeof(int));
	i = -1;
	q->dir[0][0] = 0;
	q->dir[0][1] = 1;
	q->dir[1][0] = 1;
	q->dir[1][1] = 0;
	q->dir[2][0] = -1;
	q->dir[2][1] = 0;
	q->dir[3][0] = 0;
	q->dir[3][1] = -1;
	while (++i < (*game)->map->h)
	{
		checked[i] = alloc_mem((*game)->mem_p, sizeof(int) * (*game)->map->w);
		if (!checked[i])
			free_and_exit(mem_p, game, 1, "Failed to allocate memory\n");
	}
	q->front = 0;
	q->back = 0;
}

int	path_check(char **grid, t_game **game, t_pool *mem_p)
{
	t_queue	*q;
	int		**checked;
	int		c_num_found_e[2];
	t_pos	curr;

	q = (t_queue *)alloc_mem(mem_p, sizeof(t_queue));
	checked = alloc_mem(mem_p, sizeof(int *) * (*game)->map->h);
	c_num_found_e[0] = 0;
	c_num_found_e[1] = 0;
	if (!q || !checked)
		free_and_exit(mem_p, game, 1, "Failed to allocate memory\n");
	init_vals(q, checked, game, mem_p);
	q->q[q->back++] = (t_pos){(*game)->p_x, (*game)->p_y};
	checked[(*game)->p_x][(*game)->p_y] = 1;
	while (q->front < q->back)
	{
		curr = q->q[q->front++];
		if (grid[curr.x][curr.y] == 'C')
			c_num_found_e[0]++;
		if (grid[curr.x][curr.y] == 'E')
			c_num_found_e[1] = 1;
		queue_if_valid(&curr, q, game, checked);
	}
	return (c_num_found_e[0] == (*game)->map->c && c_num_found_e[1]);
}
