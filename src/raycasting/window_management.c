/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 20:54:36 by jotong            #+#    #+#             */
/*   Updated: 2026/04/24 20:54:51 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

int	close_window(void *game)
{
	t_game	*game_tmp;

	game_tmp = (t_game *)game;
	if (game_tmp && game_tmp->mlx_ptr && game_tmp->win_ptr)
	{
		mlx_destroy_window(game_tmp->mlx_ptr, game_tmp->win_ptr);
		ft_printf("freeing memory after destroying window\n");
		game_tmp->win_ptr = NULL;
	}
	free_and_exit(&game_tmp, 0, "Window closed.");
	return (0);
}

void	*create_window(t_game **game, void *mlx)
{
	int		width;
	int		height;

	width = ((*game)->view_w);
	height = ((*game)->view_h);
	(*game)->win_ptr = mlx_new_window(mlx, width, height, "cub3d");
	if (!(*game)->win_ptr)
		free_and_exit(game, 1, "Failed to open new window.\n");
	return ((*game)->win_ptr);
}

int	handle_close(void *game_in)
{
	t_game	*game;

	game = (t_game *)game_in;
	close_window(game);
	return (0);
}
