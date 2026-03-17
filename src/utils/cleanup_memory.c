/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:35:10 by jotong            #+#    #+#             */
/*   Updated: 2026/03/17 16:39:37 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void destroy_images(t_game **game)
{
	if ((*game)->mlx_ptr)
    {
        // Destroy loaded wall textures if they exist
        if ((*game)->textures[0].img)
			mlx_destroy_image((*game)->mlx_ptr, (*game)->textures[0].img);
        if ((*game)->textures[1].img)
			mlx_destroy_image((*game)->mlx_ptr, (*game)->textures[1].img);
		if ((*game)->textures[2].img)
			mlx_destroy_image((*game)->mlx_ptr, (*game)->textures[2].img);
		if ((*game)->textures[3].img)
			mlx_destroy_image((*game)->mlx_ptr, (*game)->textures[3].img);
        // TODO: destroy main frame buffer here
        
        if ((*game)->win_ptr) // check if this is possible for Linux
            mlx_destroy_window((*game)->mlx_ptr, (*game)->win_ptr);
    }
}

void	free_mlx(t_game **game)
{
	if ((*game)->mlx_ptr && (*game)->win_ptr)
	{
		mlx_destroy_window((*game)->mlx_ptr, (*game)->win_ptr);
		(*game)->win_ptr = NULL;
	}
	if ((*game)->mlx_ptr)
	{
		mlx_destroy_display((*game)->mlx_ptr);
		free((*game)->mlx_ptr);
		(*game)->mlx_ptr = NULL;
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_and_exit(t_game **game, int status, char *msg)
{
	int	i;

	if (!game)
		return ;
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
    }
	destroy_images(game);
	free_mlx(game);
	free((*game));
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
