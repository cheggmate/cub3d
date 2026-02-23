/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:22:37 by jotong            #+#    #+#             */
/*   Updated: 2026/02/23 17:10:03 by jotong           ###   ########.fr       */
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

int	check_asset(char *f_str, t_game **game)
{
	int		fd;
	int		i;
	int		result;
	char	*f_name;
	char	*texture_dir;

	i = 2;
	texture_dir = ft_substr(f_str, 0, 2);
	if (!texture_dir)
		return (0);
	while(f_str[i] && f_str[i] == ' ') // filename can be separated by more than one space
		i++;
	f_name = ft_strdup(&f_str[i]);
	if (!f_name)
		return (0);
	fd = open(f_name, O_RDONLY); // check if i need to add a folder
	result = fd;
	if (result != -1)
	{
		if (ft_strncmp(texture_dir, "NO", 2) == 0)
			(*game)->tex_paths[0] = f_name;
		else if (ft_strncmp(texture_dir, "SO", 2) == 0)
			(*game)->tex_paths[1] = f_name;
		else if (ft_strncmp(texture_dir, "EA", 2) == 0)
			(*game)->tex_paths[2] = f_name;
		else if (ft_strncmp(texture_dir, "WE", 2) == 0)
			(*game)->tex_paths[3] = f_name;
	}
	close(fd);
	return (1);
}


// void	check_asset_list2(void)
// {
// 	if (check_asset_exist("assets/player_door_c.xpm") == -1)
// 	{
// 		write(2, "Error\nPlayer sprite not found.\n", 31);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (check_asset_exist("assets/player_door_o.xpm") == -1)
// 	{
// 		write(2, "Error\nPlayer sprite not found.\n", 31);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	check_asset_list(void)
// {
// 	if (check_asset_exist("assets/player.xpm") == -1)
// 	{
// 		write(2, "Error\nPlayer sprite not found.\n", 31);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (check_asset_exist("assets/wall.xpm") == -1)
// 	{
// 		write(2, "Error\nWall sprite not found.\n", 31);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (check_asset_exist("assets/door.xpm") == -1)
// 	{
// 		write(2, "Error\nExit sprite not found.\n", 31);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (check_asset_exist("assets/collectible.xpm") == -1)
// 	{
// 		write(2, "Error\nCollectible sprite not found.\n", 31);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (check_asset_exist("assets/floor.xpm") == -1)
// 	{
// 		write(2, "Error\nFloor sprite not found.\n", 31);
// 		exit(EXIT_FAILURE);
// 	}
// }
