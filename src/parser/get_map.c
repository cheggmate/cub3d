/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:25:26 by jotong            #+#    #+#             */
/*   Updated: 2026/04/27 00:29:14 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	set_player_pos_in_grid_to_zero(t_game **game)
{
	t_list	*node;
	int		i;

	node = (*game)->tmp_list;
	i = 0;
	while (node && i < (int)(*game)->player.pos_y)
	{
		node = node->next;
		i++;
	}
	if (node)
		((char *)node->content)[(int)(*game)->player.pos_x] = '0';
}

void	check_update_element_ctr(t_game **game, char c, int *pos)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*game)->map->start += 1;
		(*game)->player.pos_x = (double)pos[0] + 0.5;
		(*game)->player.pos_y = (double)pos[1] + 0.5;
		set_player_pos_in_grid_to_zero(game);
		update_player_direction(game, c);
	}
	else if (!(c == '1' || c == '0' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W' || c == ' '))
		free_and_exit(game, 1, "Invalid item found in map.\n");
	if ((*game)->map->start > 1)
		free_and_exit(game, 1, "More than one start pos found.\n");
}

int	populate_row(t_game **game, int row, char *line)
{
	int		pos[2];
	char	*ptr;

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
	if ((*game)->map->w < pos[0])
		(*game)->map->w = pos[0];
	return (0);
}

void	populate_grid(t_game **game, int fd, char *line)
{
	int		row;
	size_t	len;
	char	*next_ptr;

	row = 0;
	while (line && line[0] != '\n')
	{
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] != '\n')
			len += 1;
		if (populate_row(game, row, line) != 0)
			free_and_exit(game, 1, "Issue populating grid.\n");
		next_ptr = get_next_line(fd);
		line = next_ptr;
		row++;
	}
	if ((*game)->map->w <= 4 || (*game)->map->h <= 4)
		free_and_exit(game, 1, "Map too small, impossible to win.\n");
}
