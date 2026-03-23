/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:25:26 by jotong            #+#    #+#             */
/*   Updated: 2026/03/23 15:18:55 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_map.c: Reads the map into a 2D array (char **map).

#include "cub3d.h"
#include "libft.h"

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

static void set_player_pos_in_grid_to_zero(t_game **game)
{
    t_list  *node;
    int     i;

    node = (*game)->tmp_list;
    i = 0;
    while (node && i < (int)(*game)->player.pos_y - 1)
    {
        node = node->next;
        i++;
    }
    if (node)
		((char *)node->content)[(int)(*game)->player.pos_x] = '0';
        
}

void	check_update_element_ctr(t_game **game, char c, int *pos) // from solong
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		printf("player found: pos_x=%d pos_y=%d char='%c'\n", pos[0], pos[1], c);
		(*game)->map->start += 1;
		(*game)->player.pos_x = pos[0];
		(*game)->player.pos_y = pos[1];
		set_player_pos_in_grid_to_zero(game);
		update_player_direction(game, c);
	}
	else if (!(c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' '))
	{
		printf("found '%c' at pos %d\n", c, pos[1]);
		free_and_exit(game, 1, "Invalid item found in map.\n");
	}
	if ((*game)->map->start > 1)
		free_and_exit(game, 1, "More than one start pos found.\n");
}

int populate_row(t_game **game, int row, char *line)
{
    int     pos[2];
    char    *ptr;

    pos[1] = row;
    if (!(*game)->tmp_list)
        (*game)->tmp_list = create_tmp_list(line);
    else if (add_row_to_list(&(*game)->tmp_list, line) != 0)
        return (-1);
    ptr = line;
    pos[0] = 0;
    while (ptr && *ptr && *ptr != '\n')
    {
        check_update_element_ctr(game, *ptr, pos);
        ptr++;
        pos[0]++;
    }
    (*game)->map->h += 1;
	printf("populate_row: row=%d, line='%s'\n", row, line);
    if ((*game)->map->w < pos[0])
        (*game)->map->w = pos[0];
    return (0);
}

static void	populate_grid(t_game **game, int fd, char *line)
{
	int		row;
	size_t	len;
	char	*next_ptr;

	row = 1;
	while (line)
	{
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] != '\n')
			len += 1;
		if (populate_row(game, row, line) != 0)
			free_and_exit(game, 1, "Issue populating grid.\n");
		next_ptr = get_next_line(fd);
        free(line);    // Free the line we just finished with
        line = next_ptr;
		row++;
	}
	// free_safely(&line);
	printf("(*game)->map->w = %d, (*game)->map->h = %d\n", (*game)->map->w , (*game)->map->h);
	if ((*game)->map->w <= 4 || (*game)->map->h <= 4)
		free_and_exit(game, 1, "Map too small, impossible to win.\n");
}

void	print_map(t_map *map) // from solong
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

void copy_map_to_grid(t_game **game)
{
    int     row;
    t_list  *curr;
    char    *content;
    int     content_len;

    row = 0;
    curr = (*game)->tmp_list;
    while (row < (*game)->map->h && curr)
    {
        content = (char *)curr->content;
        content_len = ft_strlen(content);
        int col = 0;
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
	// if (populate_row(game, 0, line) != 0)  // handle first line here
    //     free_and_exit(game, 1, "Issue populating first row.\n");
	populate_grid(game, (*game)->map->fd, line);
	close((*game)->map->fd);
	init_grid(game);
	copy_map_to_grid(game);
	if ((*game)->map->h == 0)
		free_and_exit(game, 1, "Empty map file provided.\n");
	print_map((*game)->map);
	if (!is_map_closed((*game)))
		free_and_exit(game, 1, "Map is not closed/surrounded by walls.\n");
	set_view_dimensions(game);
}
