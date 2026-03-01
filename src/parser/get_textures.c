/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:22:37 by jotong            #+#    #+#             */
/*   Updated: 2026/03/01 13:33:57 by jotong           ###   ########.fr       */
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

static int rgb_to_int(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

static int	save_colour(char **split_f_str, int i, t_game **game)
{
	char	**colour; //rgb as provided in cub
	int		surface;
	int		i_colour[3];

	surface = split_f_str[i];
	colour = ft_split(split_f_str[i+1], ',');
	if (!colour || char_arr_size(colour) != 3)
		return (free_array(colour), -1);
	i_colour[0] = ft_atoi(colour[0]);
	i_colour[1] = ft_atoi(colour[1]);
	i_colour[2] = ft_atoi(colour[2]);
	if (!arr_in_limit(i_colour[0], 0, 255) \
		|| !arr_in_limit(i_colour[1], 0, 255) \
		|| !arr_in_limit(i_colour[2], 0, 255))
		return (free_array(colour), -1);
	(*game)->floor_color = rgb_to_int(i_colour[0], i_colour[1], i_colour[2]);
	return (free_array(colour), 1);
}

static int	save_texture(char **split_f_str, int i, t_game **game)
{
	int		fd;
	int		pos;
	char	*f_name;
	int		pxl_data[3];
	
	f_name = split_f_str[i+1];
	fd = open(f_name, O_RDONLY);
	close(fd);
	if (fd < 1)
		return (-1);
	if (ft_strncmp(split_f_str[i], "NO", 2) == 0)
		pos = 0;
	else if (ft_strncmp(split_f_str[i], "SO", 2) == 0)
		pos = 1;
	else if (ft_strncmp(split_f_str[i], "EA", 2) == 0)
		pos = 2;
	else if (ft_strncmp(split_f_str[i], "WE", 2) == 0)
		pos = 3;
	else
		return (-1);
	(*game)->tex_path[pos] = f_name;
	(*game)->textures[pos].img = mlx_xpm_file_to_image((*game)->mlx, f_name, &((*game)->textures[pos].width), &((*game)->textures[pos].height));
	(*game)->textures[pos].addr = mlx_get_data_addr((*game)->textures[pos].img, &pxl_data[0], &pxl_data[1], &pxl_data[2]);
	return (0);
}

// NO -> 0, SO -> 1, EA -> 2, WE -> 3
int	check_asset(char *f_str, t_game **game) // f_str here contains the full line from the .cub file
{
	int		fd;
	int		i;
	char	**split_f_str;
	// char	*f_name;
	char	*texture_dir;

	i = 0;
	split_f_str = ft_split(f_str, ' ');
	while (split_f_str[i])
	{
		if (ft_strncmp(split_f_str[i], "NO", 2) == 0 
			|| ft_strncmp(split_f_str[i], "SO", 2) == 0
			|| ft_strncmp(split_f_str[i], "EA", 2) == 0
			|| ft_strncmp(split_f_str[i], "WE", 2) == 0)
		{
			texture_dir = ft_strdup(split_f_str[i]);
			if (texture_dir == NULL)
				return (free_array(split_f_str), -1);
			if (save_texture(split_f_str, i, game) != 0)
				return (free_array(split_f_str), -1);
		}
		else if (ft_strncmp(split_f_str[i], "F", 1) == 0
				|| ft_strncmp(split_f_str[i], "C", 1) == 0)
		{
			if (save_colour(split_f_str, i, game) != 0)
				return (free_array(split_f_str), -1);
		}
		i++;
	}
	// texture_dir = ft_substr(f_str, 0, 2);
	// if (!texture_dir)
	// 	return (0);
	// while(f_str[i] && f_str[i] == ' ') // filename can be separated by more than one space
	// 	i++;
	// f_name = ft_strdup(&f_str[i]);
	// if (!f_name)
	// 	return (0);
	// fd = open(f_name, O_RDONLY); // check if i need to add a folder
	// if (fd != -1)
	// {
	// 	if (ft_strncmp(texture_dir, "NO", 2) == 0)
	// 		(*game)->tex_paths[0] = f_name;
	// 	else if (ft_strncmp(texture_dir, "SO", 2) == 0)
	// 		(*game)->tex_paths[1] = f_name;
	// 	else if (ft_strncmp(texture_dir, "EA", 2) == 0)
	// 		(*game)->tex_paths[2] = f_name;
	// 	else if (ft_strncmp(texture_dir, "WE", 2) == 0)
	// 		(*game)->tex_paths[3] = f_name;
	// }
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
