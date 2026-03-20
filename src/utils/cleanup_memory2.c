/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_memory2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:38 by jotong            #+#    #+#             */
/*   Updated: 2026/03/20 10:04:04 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_file(int fd)
{
	if (fd > 2)
		close(fd);
}

void	free_fd_map(t_game **game)
{
	int	i;

	if (game && *game && (*game)->map && (*game)->map->fd > 2)
	{
		close((*game)->map->fd);
		(*game)->map->fd = -1;
	}
	if ((*game)->map && (*game)->map->grid)
    {
        i = 0;
        while (i < (*game)->map->h)
            free((*game)->map->grid[i++]);
        free((*game)->map->grid);
		free((*game)->map);
		(*game)->map = NULL;
    }
}

void	free_safely(char **line)
{
	if (!(*line))
		return;
	free((*line));
	(*line) = NULL;
}