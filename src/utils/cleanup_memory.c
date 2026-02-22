/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:35:10 by jotong            #+#    #+#             */
/*   Updated: 2026/02/22 14:25:43 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

// void	free_pool(t_pool *mem_p)
// {
// 	if (mem_p->head)
// 	{
// 		free(mem_p->head);
// 		mem_p->head = NULL;
// 	}
// 	free(mem_p);
// 	mem_p = NULL;
// }

void	free_and_exit(t_game **game, int status, char *msg)
{
	if (game && *game && (*game)->map && (*game)->map->fd >= 0)
	{
		close((*game)->map->fd);
		(*game)->map->fd = -1;
	}
	destroy_images(game);
	free_mlx(game);
	// free_pool(mem_p);
	if (status == 1)
	{
		write(2, "Error\n", 6);
		write(2, msg, ft_strlen(msg));
		exit(EXIT_FAILURE);
	}
	else
	{
		(void)msg;
		exit(EXIT_SUCCESS);
	}
}
