/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:01:43 by jotong            #+#    #+#             */
/*   Updated: 2026/02/19 16:56:34 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parser.c: Orchestrates the reading of the .cub file.

#include "cub3d.h"
#include "libft.h"

int parse_cub_file(char *file)
{
	int 	fd;
	char	*line;
	char	line_1;

	if (!file)
		return (0);
	fd = open(file, 0_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line;
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
		else if (ft_strncmp(line, "NO ", 3) == 0)
			// send to flow to unpack file for north texture
		else if (ft_strncmp(line, "SO ", 3) == 0)
			// send to flow to unpack file for south texture
		else if (ft_strncmp(line, "WE ", 3) == 0)
			// send to flow to unpack file for west texture
		else if (ft_strncmp(line, "EA ", 3) == 0)
			// send to flow to unpack file for east texture
		else if (ft_strncmp(line, "F ", 2) == 0)
			// send to flow to unpack colour of floor
		else if (ft_strncmp(line, "C ", 2) == 0)
			// send to flow to unpack colour of ceiling
		else if (ft_strchr("10NSEW", line_1) == 0)
			// send to flow to unpack map
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (1);
}
