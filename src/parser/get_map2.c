/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 08:15:32 by jotong            #+#    #+#             */
/*   Updated: 2026/04/29 14:12:28 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			ft_printf("%c", map->grid[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
}

void	copy_map_to_grid(t_game **game)
{
	int		row;
	t_list	*curr;
	char	*content;
	int		content_len;
	int		col;

	row = 0;
	curr = (*game)->tmp_list;
	while (row < (*game)->map->h && curr)
	{
		content = (char *)curr->content;
		content_len = ft_strlen(content);
		col = 0;
		while (col < content_len && col < (*game)->map->w)
		{
			(*game)->map->grid[row][col] = content[col];
			col++;
		}
		curr = curr->next;
		row++;
	}
}

void	load_map(char *f_map, t_game **game, char *line)
{
	if (!f_map)
		free_and_exit(game, 1, "failed to allocate memory.\n");
	populate_grid(game, (*game)->map->fd, line);
	close((*game)->map->fd);
	init_grid(game);
	copy_map_to_grid(game);
	if ((*game)->map->h == 0)
		free_and_exit(game, 1, "Empty map file provided.\n");
	if (!is_map_closed((*game)))
		free_and_exit(game, 1, "Map is not closed/surrounded by walls.\n");
}

void	update_player_direction(t_game **game, char c)
{
	if (c == 'N' || c == 'S')
	{
		(*game)->player.dir_x = 0;
		(*game)->player.dir_y = 1;
		(*game)->player.plane_x = -0.66;
		(*game)->player.plane_y = 0;
		if (c == 'N')
		{
			(*game)->player.dir_y *= -1;
			(*game)->player.plane_x *= -1;
		}
	}
	else if (c == 'E' || c == 'W')
	{
		(*game)->player.dir_x = 1;
		(*game)->player.dir_y = 0;
		(*game)->player.plane_x = 0;
		(*game)->player.plane_y = 0.66;
		if (c == 'W')
		{
			(*game)->player.dir_x *= -1;
			(*game)->player.plane_y *= -1;
		}
	}
}
