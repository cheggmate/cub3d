/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:22:37 by jotong            #+#    #+#             */
/*   Updated: 2026/04/24 20:40:30 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static int	get_texture_pos(char **split_f_str, int i)
{
	if (ft_strncmp(split_f_str[i], "NO", 2) == 0)
		return (0);
	else if (ft_strncmp(split_f_str[i], "SO", 2) == 0)
		return (1);
	else if (ft_strncmp(split_f_str[i], "EA", 2) == 0)
		return (2);
	else if (ft_strncmp(split_f_str[i], "WE", 2) == 0)
		return (3);
	else
		return (-1);
}

static int	init_tex_path(t_game **game, char *f_name, int pos)
{
	int	fd;
	int	len;

	if (!f_name)
		return (-1);
	len = ft_strlen(f_name);
	if (len > 0 && f_name[len - 1] == '\n')
		f_name[len - 1] = '\0';
	fd = open(f_name, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open texture file: [%s]\n", f_name);
		return (-1);
	}
	close(fd);
	if ((*game)->tex_paths[pos] != NULL)
		return (-1);
	(*game)->tex_paths[pos] = ft_strdup(f_name);
	if (!(*game)->tex_paths[pos])
		return (-1);
	return (0);
}

static int	load_tex_to_mlx(t_game **game, char *f_name, int pos)
{
	t_texture	*tex;

	tex = &(*game)->textures[pos];
	tex->img = mlx_xpm_file_to_image((*game)->mlx_ptr, f_name,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error: MLX failed to load texture: %s\n", f_name);
		return (-1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		printf("Error: MLX failed to get texture data.\n");
		return (-1);
	}
	return (0);
}

static int	save_texture(char **split_f_str, int i, t_game **game)
{
	int		pos;
	char	*f_name;

	pos = get_texture_pos(split_f_str, i);
	if (pos == -1)
		return (-1);
	f_name = split_f_str[i + 1];
	if (init_tex_path(game, f_name, pos) == -1)
		return (-1);
	if (load_tex_to_mlx(game, f_name, pos) == -1)
		return (-1);
	return (0);
}

int	check_asset_tex(char *f_str, t_game **game)
{
	int		i;
	char	**split_f_str;

	i = 0;
	split_f_str = ft_split(f_str, ' ');
	if (char_arr_size(split_f_str) != 2)
	{
		free_array(split_f_str);
		return (-1);
	}
	while (split_f_str[i])
	{
		if (ft_strncmp(split_f_str[i], "NO", 2) == 0
			|| ft_strncmp(split_f_str[i], "SO", 2) == 0
			|| ft_strncmp(split_f_str[i], "EA", 2) == 0
			|| ft_strncmp(split_f_str[i], "WE", 2) == 0)
		{
			if (save_texture(split_f_str, i, game) != 0)
				return (free_array(split_f_str), -1);
			break ;
		}
		i++;
	}
	free_array(split_f_str);
	return (0);
}
