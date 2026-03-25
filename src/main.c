/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:38:44 by jotong            #+#    #+#             */
/*   Updated: 2026/03/25 18:06:46 by jotong           ###   ########.fr       */
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
	create_window(&game, game->mlx_ptr);
	if (parse_cub_file(argv[1], &game) != 0)
	{
		printf("issue occurred, aborting..");
		return (1);
	}
	printf("cub file ingestion done\n");
	if (MODE == 1)
	{
		game->img.img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
		if (!game->img.img_ptr)
		    free_and_exit(&game, 1, "Failed to create MLX image");
		game->img.addr = mlx_get_data_addr(game->img.img_ptr, 
		    &game->img.bpp, 
		    &game->img.line_length, 
		    &game->img.endian);
		printf("after mlx_get_data_addr\n ");
		mlx_loop_hook(game->mlx_ptr, render_raycast, game);
		printf("after mlx loop hook\n");
        mlx_hook(game->win_ptr, 2, 1L << 0, key_press, game);
		printf("after mlx hook keypress\n ");
        mlx_hook(game->win_ptr, 3, 1L << 1, key_release, game);
        mlx_hook(game->win_ptr, 17, 0, close_window, game);
        
        mlx_loop(game->mlx_ptr);
	}
	else if (MODE == 2) // putting this temporarily so valgrind doesnt complain. normally the exit button should trigger closure.
		free_and_exit(&game, 0, "Completed");
	
	return (0);
}
