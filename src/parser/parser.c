/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:01:43 by jotong            #+#    #+#             */
/*   Updated: 2026/03/01 09:11:55 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parser.c: Orchestrates the reading of the .cub file.

#include "cub3d.h"
#include "libft.h"

static int	check_file(int *fd, )

int parse_cub_file(char *file, t_game **game)
{
	int 	fd;
	char	*line;
	char	line_1;
	bool	parsed_map;
	
	parsed_map = false;
	if (!file)
		return (0);
	fd = open(file, 0_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		line_1 = line[0]; 
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if (!parsed_map && ft_strncmp(line, "NO ", 3) == 0 && check_asset(line))
			check_asset(line, game); // extract pixels ands store in game->textures[0]
		else if (!parsed_map && ft_strncmp(line, "SO ", 3) == 0 && check_asset(line))
			check_asset(line, game); // extract pixels ands store in game->textures[1]
		else if (!parsed_map && ft_strncmp(line, "EA ", 3) == 0 && check_asset(line))
			check_asset(line, game); // extract pixels ands store in game->textures[2]
		else if (!parsed_map && ft_strncmp(line, "WE ", 3) == 0 && check_asset(line))
			check_asset(line, game); // extract pixels ands store in game->textures[3]
		else if (!parsed_map && ft_strncmp(line, "F ", 2) == 0 && check_asset(line))
			// extract colour ands store in game->floor_color
		else if (!parsed_map && ft_strncmp(line, "C ", 2) == 0 && check_asset(line))
			// extract colour ands store in game->ceiling_color
		else if (ft_strchr("10NSEW", line_1) == 0)
		{
			load_map(file, game);
			parsed_map = 1; // map must be at the end of the file.
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (1);
}
