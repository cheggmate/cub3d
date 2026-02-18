/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:22:37 by jotong            #+#    #+#             */
/*   Updated: 2026/02/18 16:22:50 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_textures.c: Specifically handles the NO, SO, WE, EA lines.

#include "cub3d.h"
#include "libft.h"
#ifdef __APPLE__
# include "minilibx_opengl_20191021/mlx.h"
#elif __linux__
# include "minilibx-linux/mlx.h"
#endif

void	check_asset_list2(void)
{
	if (check_asset_exist("assets/player_door_c.xpm") == -1)
	{
		write(2, "Error\nPlayer sprite not found.\n", 31);
		exit(EXIT_FAILURE);
	}
	if (check_asset_exist("assets/player_door_o.xpm") == -1)
	{
		write(2, "Error\nPlayer sprite not found.\n", 31);
		exit(EXIT_FAILURE);
	}
}

void	check_asset_list(void)
{
	if (check_asset_exist("assets/player.xpm") == -1)
	{
		write(2, "Error\nPlayer sprite not found.\n", 31);
		exit(EXIT_FAILURE);
	}
	if (check_asset_exist("assets/wall.xpm") == -1)
	{
		write(2, "Error\nWall sprite not found.\n", 31);
		exit(EXIT_FAILURE);
	}
	if (check_asset_exist("assets/door.xpm") == -1)
	{
		write(2, "Error\nExit sprite not found.\n", 31);
		exit(EXIT_FAILURE);
	}
	if (check_asset_exist("assets/collectible.xpm") == -1)
	{
		write(2, "Error\nCollectible sprite not found.\n", 31);
		exit(EXIT_FAILURE);
	}
	if (check_asset_exist("assets/floor.xpm") == -1)
	{
		write(2, "Error\nFloor sprite not found.\n", 31);
		exit(EXIT_FAILURE);
	}
}
