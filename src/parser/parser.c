/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:01:43 by jotong            #+#    #+#             */
/*   Updated: 2026/03/23 16:02:58 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parser.c: Orchestrates the reading of the .cub file.

#include "cub3d.h"
#include "libft.h"

static int	load_individual_section(char *file, t_game **game, int *parsed_map, char *line)
{
	char	line_1;

	line_1 = line[0];
	if (!*parsed_map && (ft_strncmp(line, "NO ", 3) == 0 \
			|| ft_strncmp(line, "SO ", 3) == 0 \
			|| ft_strncmp(line, "EA ", 3) == 0 \
			|| ft_strncmp(line, "WE ", 3) == 0))
			return (check_asset_tex(line, game));
	else if (!*parsed_map && (ft_strncmp(line, "F ", 2) == 0 \
			|| ft_strncmp(line, "C ", 2) == 0))
		return (check_asset_colour(line, game));
	else if (ft_strchr("10NSEW ", line_1) != NULL)
	{
		load_map(file, game, line);
		*parsed_map = 1; // map must be at the end of the file.
		return (0);
	}
	return (-1);
}

static int	check_all_texs_colours_exist(t_game **game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!(*game)->textures[i].img)
			return (-1);
		i++;
	}
	printf("textures exist\n");
	if ((*game)->ceiling_colour == -1 || (*game)->floor_colour == -1)
		return (-1);
	return (0);
}

static void	check_and_store_texs_and_colours(char *file, t_game **game,
				int fd, int *parsed_map)
{
	char	*line;
	
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free_safely(&line);
			continue ;
		}
		if (load_individual_section(file, game, parsed_map, line) != 0)
			free_and_exit(game, 1, "Invalid configuration line.\n");
		if (*parsed_map) // Stop immediately once map is found/freed
			return ;
		free_safely(&line);
	}
}

int parse_cub_file(char *file, t_game **game)
{
	int 	fd;
	int		parsed_map;

	parsed_map = 0;
	if (!file)
		return (0);
	fd = open(file, O_RDONLY);
	printf("before storing fd\n");
	(*game)->map->fd = fd;
	printf("after storing fd\n");
	if (fd < 0)
		return (close_file(fd), 0);
	check_and_store_texs_and_colours(file, game, fd, &parsed_map);
	printf("tex 0: %s\n", (*game)->tex_paths[0]);
	printf("tex 1: %s\n", (*game)->tex_paths[1]);
	printf("tex 2: %s\n", (*game)->tex_paths[2]);
	printf("tex 3: %s\n", (*game)->tex_paths[3]);
	printf("floor colour: %d\n", (*game)->floor_colour);
	printf("ceiling_colour: %d\n", (*game)->ceiling_colour);
	print_map((*game)->map);
	if (check_all_texs_colours_exist(game) != 0)
		return (close_file(fd), free_and_exit(game, 1, "Invalid content in .cub file.\n"), 0);
	printf("done parsing cub file\n");
	close_file(fd);
	return (0);
}
