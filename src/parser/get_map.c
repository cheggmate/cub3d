/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:25:26 by jotong            #+#    #+#             */
/*   Updated: 2026/03/01 13:34:58 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_map.c: Reads the map into a 2D array (char **map).

#include "cub3d.h"
#include "libft.h"

void	populate_row(t_game **game, int row, char *line)
{
	int		pos[2];

	pos[0] = row;
	pos[1] = 0;
	if (!((*game)->map->grid[row]))
		free_and_exit(game, 1, "Failed to alloc mem for grid.\n");
	while (*line && *line != '\n')
	{
		if (((row == 0 || row == (*game)->map->h -  1) && *line != '1'
				&& pos[1] <= (*game)->map->w - 1)
			|| ((pos[1] == 0 || pos[1] == (*game)->map->w - 1) && *line != '1'))
				free_and_exit(game, 1, "Map not enclosed by walls.\n");	
		if (*line != '\n')
			(*game)->map->grid[row][pos[1]] = *line;
		else if (*line == '\n')
		{
			(*game)->map->grid[row][pos[1]] = '\0';
			break ;
		}
		check_update_element_ctr(game, *line, pos);
		pos[1]++;
		line++;
	}
}

static void	populate_grid(t_game **game, int fd)
{
	char	*line;
	int		row;
	size_t	len;

	row = 1;
	while (row < (*game)->map->h)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] != '\n')
			len += 1;
		if ((len != (size_t)(*game)->map->w && row <= (*game)->map->h - 1))
			free_and_exit(game, 1, "Map is not rectangular.\n");
		populate_row(game, row, line);
		free(line);
		line = NULL;
		row++;
	}
	if ((*game)->map->w <= 4 || (*game)->map->h <= 4)
		free_and_exit(game, 1, "Map too small, impossible to win.\n");
}



void	load_map(char *f_map, t_game **game)
{
	char	*line;

	line = NULL;
	// mem_p = init_mem_pool(POOL_SIZE);
	if (!f_map)
		free_and_exit(game, 1, "failed to allocate memory.\n");
	init_game(game, f_map);
	init_grid(f_map, game);
	if ((*game)->map->h == 0)
		free_and_exit(game, 1, "Empty map file provided.\n");
	line = get_next_line((*game)->map->fd);
	populate_row(game, 0, line);
	free(line);
	line = NULL;
	populate_grid(game, (*game)->map->fd);
	if ((*game)->map->c == 0)
		free_and_exit(game, 1, "No collectibles found.\n");
	close((*game)->map->fd);
	print_map((*game)->map);
	set_view_dimensions(game);
	if (!path_check((*game)->map->grid, game, (*game)->mem_p))
		free_and_exit(game, 1, "Error: Map is not solvable.");
	render_map(game);
}


