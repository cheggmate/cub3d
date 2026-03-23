/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:38:44 by jotong            #+#    #+#             */
/*   Updated: 2026/03/24 00:30:29 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (argc != 2)
		return (write(2, "Error\nincorrect number of inputs!\n", 34), 1);
	init_game(&game, argv[1]);
	if (parse_cub_file(argv[1], &game) != 0)
	{
		printf("issue occurred, aborting..");
		return (1);
	}
		
	printf("cub file ingestion done/n");
	if (MODE == 1)
	{
		mlx_loop_hook(game->mlx_ptr, &render_raycast, game);
		mlx_hook(game->win_ptr, 2, 1L << 0, &key_press, &game); // hooks for keys and closing window
		mlx_hook(game->win_ptr, 3, 1L << 1, &key_release, &game); // hooks for keys and closing window
		mlx_hook(game->win_ptr, 17, 0, &close_window, &game);
		mlx_loop(game->mlx_ptr);
	}
	else if (MODE == 2) // putting this temporarily so valgrind doesnt complain. normally the exit button should trigger closure.
		free_and_exit(&game, 0, "Completed");
	return (0);
}
