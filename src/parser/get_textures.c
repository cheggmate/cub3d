/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:22:37 by jotong            #+#    #+#             */
/*   Updated: 2026/03/01 14:30:57 by jotong           ###   ########.fr       */
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
int	check_asset_tex(char *f_str, t_game **game) // f_str here contains the full line from the .cub file
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
		i++;
	}
	close(fd);
	return (1);
}
