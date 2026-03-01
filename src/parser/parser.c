/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:01:43 by jotong            #+#    #+#             */
/*   Updated: 2026/03/01 14:33:53 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parser.c: Orchestrates the reading of the .cub file.

#include "cub3d.h"
#include "libft.h"

static int	check_all_texs_colours_exist(t_game **game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(*game)->texture[i])
			return (0);
		i++;
	}
	if (!(*game)->ceiling_colour || !(*game)->floor_colour)
		return (0);
	return (1);
	
}

static void	check_and_store_texs_and_colours(char *file, t_game **game,
				char *line, int *parsed_map)
{
	char	line_1;
	
	while (line)
	{
		line_1 = line[0]; 
		if (!*parsed_map && (ft_strncmp(line, "NO ", 3) == 0 \
				|| ft_strncmp(line, "SO ", 3) == 0 \
				|| ft_strncmp(line, "EA ", 3) == 0 \
				|| ft_strncmp(line, "WE ", 3) == 0))
			check_asset_tex(line, game);
		else if (!*parsed_map && (ft_strncmp(line, "F ", 2) == 0 \
				|| ft_strncmp(line, "C ", 2) == 0))
			check_asset_colours(line, game);
		else if (ft_strchr("10NSEW ", line_1) == 0)
		{
			load_map(file, game);
			*parsed_map = 1; // map must be at the end of the file.
		}
		free(line);
		line = get_next_line(fd);
	}
}

int parse_cub_file(char *file, t_game **game)
{
	int 	fd;
	char	*line;
	int		parsed_map;
	
	parsed_map = 0;
	if (!file)
		return (0);
	fd = open(file, 0_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (0);
	check_and_store_texs_and_colours(file, game, line, &parsed_map);
	if (line)
		free(line);
	if (!check_all_texs_colours_exist(game))
		return (free_and_exit(game, 1, "Invalid content in .cub file."), 0);
	return (1);
}
