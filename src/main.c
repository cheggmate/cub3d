/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:38:44 by jotong            #+#    #+#             */
/*   Updated: 2026/02/18 16:38:51 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include "libft.h"
#ifdef __APPLE__
# include "minilibx_opengl_20191021/mlx.h"
#elif __linux__
# include "minilibx-linux/mlx.h"
#endif

int	main(int argc, char **argv)
{
	t_game	*game;
	int		fd;

	game = NULL;
	if (argc != 2)
		return (write(2, "Error\nincorrect number of inputs!\n", 34), 1);
	check_asset_list();
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (write(2, "Error\nInvalid file\n", 19), 1);
	}
	load_map(argv[1], &game);
	mlx_loop(game->mlx);
	return (0);
}
