/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:35:10 by jotong            #+#    #+#             */
/*   Updated: 2026/02/22 16:50:48 by jotong           ###   ########.fr       */
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

static void destroy_images(t_game **game)
{
	if (game->mlx_ptr)
    {
        // Destroy loaded wall textures if they exist
        if (game->tex_north)
			mlx_destroy_image(game->mlx_ptr, game->tex_north);
        if (game->tex_south)
			mlx_destroy_image(game->mlx_ptr, game->tex_south);
		if (game->tex_east)
			mlx_destroy_image(game->mlx_ptr, game->tex_east);
		if (game->tex_west)
			mlx_destroy_image(game->mlx_ptr, game->tex_east);
        // TODO: destroy main frame buffer here
        
        if (game->win_ptr) // check if this is possible for Linux
            mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    }
}

void	free_and_exit(t_game **game, int status, char *msg)
{
	if (!game)
		return ;
	if (game && *game && (*game)->map && (*game)->map->fd >= 0)
	{
		close((*game)->map->fd);
		(*game)->map->fd = -1;
	}
	if (game->map && game->map->grid)
    {
        i = 0;
        while (i < game->map->h)
            free(game->map->grid[i++]);
        free(game->map->grid);
    }
	destroy_images(game);
	free(game);
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

void free_checked(int **checked, int height)
{
    int i;

    if (!checked)
        return;
    i = 0;
    while (i < height)
    {
        if (checked[i])
            free(checked[i]);
        i++;
    }
    free(checked);
}
