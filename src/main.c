/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:38:44 by jotong            #+#    #+#             */
/*   Updated: 2026/03/21 16:47:45 by jotong           ###   ########.fr       */
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
	if (parse_cub_file(argv[1], &game) == 0)
		return (1);
	printf("cub file ingestion done/n");
	if (MODE == 1)
		mlx_loop(game->mlx_ptr);
	free(game);
	return (0);
}
