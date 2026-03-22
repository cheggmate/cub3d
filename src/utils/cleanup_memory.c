/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:35:10 by jotong            #+#    #+#             */
/*   Updated: 2026/03/22 13:39:31 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static void free_tex_paths(t_game **game)
{
    int i;

    if (!(*game)->tex_paths)
        return ;
    i = 0;
    while (i < 4)
    {
        if ((*game)->tex_paths[i])
            free((*game)->tex_paths[i]);
        i++;
    }
    free((*game)->tex_paths);
    (*game)->tex_paths = NULL;
}

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
		free_tex_paths(game);
        // TODO: destroy main frame buffer here
        
        if ((*game)->win_ptr) // check if this is possible for Linux
            mlx_destroy_window((*game)->mlx_ptr, (*game)->win_ptr);
    }
}

void    free_mlx(t_game **game)
{
    if (!(*game)->mlx_ptr)
        return ;
    if ((*game)->win_ptr)
    {
        mlx_destroy_window((*game)->mlx_ptr, (*game)->win_ptr);
        (*game)->win_ptr = NULL;
    }
    mlx_destroy_display((*game)->mlx_ptr); // specific to linux
    free((*game)->mlx_ptr);
    (*game)->mlx_ptr = NULL;
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

void    free_and_exit(t_game **game, int status, char *msg)
{
    if (!game || !*game)
        exit(status);
    if ((*game)->map && (*game)->map->grid)
        free_array((*game)->map->grid);
    if ((*game)->map)
        free((*game)->map);
    if ((*game)->tmp_list)
        ft_lstclear(&(*game)->tmp_list, free);
    destroy_images(game);
    free_mlx(game);
    free(*game);
    if (status != 0)
    {
        write(2, "Error\n", 6);
        if (msg)
            write(2, msg, ft_strlen(msg));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
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
