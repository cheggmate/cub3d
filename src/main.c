/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:38:44 by jotong            #+#    #+#             */
/*   Updated: 2026/03/15 16:26:38 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	int		fd;

	game = NULL;
	if (argc != 2)
		return (write(2, "Error\nincorrect number of inputs!\n", 34), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (write(2, "Error\nInvalid file\n", 19), 1);
	}
	if (parse_cub_file(argv[1], &game) == 0)
		return (1);
	// mlx_loop(game->mlx);
	printf("cub file ingestion done");
	return (0);
}
