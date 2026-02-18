/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:25:26 by jotong            #+#    #+#             */
/*   Updated: 2026/02/18 16:32:34 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_map.c: Reads the map into a 2D array (char **map).

#include "cub3d.h"
#include "libft.h"

void	populate_row(t_pool *mem_p, t_game **game, int row, char *line)
{
	int		pos[2];

	pos[0] = row;
	pos[1] = 0;
	if (!((*game)->map->grid[row]))
		free_and_exit(mem_p, game, 1, "Failed to alloc mem for grid.\n");
	while (*line && *line != '\n')
	{
		if (((row == 0 || row == (*game)->map->h -  1) && *line != '1'
				&& pos[1] <= (*game)->map->w - 1)
			|| ((pos[1] == 0 || pos[1] == (*game)->map->w - 1) && *line != '1'))
				free_and_exit(mem_p, game, 1, "Map not enclosed by walls.\n");	
		if (*line != '\n')
			(*game)->map->grid[row][pos[1]] = *line;
		else if (*line == '\n')
		{
			(*game)->map->grid[row][pos[1]] = '\0';
			break ;
		}
		check_update_element_ctr(mem_p, game, *line, pos);
		pos[1]++;
		line++;
	}
}

static void	populate_grid(t_game **game, t_pool *mem_p, int fd)
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
			free_and_exit(mem_p, game, 1, "Map is not rectangular.\n");
		populate_row(mem_p, game, row, line);
		free(line);
		line = NULL;
		row++;
	}
	if ((*game)->map->w <= 4 || (*game)->map->h <= 4)
		free_and_exit(mem_p, game, 1, "Map too small, impossible to win.\n");
}

void	initialise_map_values(t_game **game, char *f_map)
{
	get_map_edges(game, f_map);
	(*game)->map->c = 0;
	(*game)->map->exit = 0;
	(*game)->map->start = 0;
	(*game)->map->p_start_x = 0;
	(*game)->map->p_start_y = 0;
}

void	init_grid(t_pool *mem_p, char *f_map, t_game **game)
{
	int		i;

	i = 0;
	(*game)->map->fd = open(f_map, O_RDONLY);
	(*game)->map->grid = alloc_mem(mem_p,
			sizeof(char *) * ((*game)->map->h + 1));
	if (!(*game)->map->grid)
		free_and_exit(mem_p, game, 1, "Failed to alloc mem for grid.\n");
	while (i < (*game)->map->h)
	{
		(*game)->map->grid[i] = alloc_mem(mem_p,
				sizeof(char) * ((*game)->map->w + 1));
		if (!((*game)->map->grid[i]))
			free_and_exit(mem_p, game, 1, "Failed to alloc mem for grid.\n");
		i++;
	}
}

void	load_map(char *f_map, t_game **game)
{
	t_pool	*mem_p;
	char	*line;

	line = NULL;
	mem_p = init_mem_pool(POOL_SIZE);
	if (!f_map)
		free_and_exit(mem_p, game, 1, "failed to allocate memory pool.\n");
	init_game(mem_p, game, f_map);
	init_grid(mem_p, f_map, game);
	if ((*game)->map->h == 0)
		free_and_exit(mem_p, game, 1, "Empty map file provided.\n");
	line = get_next_line((*game)->map->fd);
	populate_row(mem_p, game, 0, line);
	free(line);
	line = NULL;
	populate_grid(game, mem_p, (*game)->map->fd);
	if ((*game)->map->c == 0)
		free_and_exit(mem_p, game, 1, "No collectibles found.\n");
	close((*game)->map->fd);
	print_map((*game)->map);
	set_view_dimensions(game);
	if (!path_check((*game)->map->grid, game, (*game)->mem_p))
		free_and_exit(mem_p, game, 1, "Error: Map is not solvable.");
	render_map(&mem_p, game);
}


