/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:22:37 by jotong            #+#    #+#             */
/*   Updated: 2026/03/20 15:24:57 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_textures.c: Specifically handles the NO, SO, WE, EA lines.

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static int  save_texture(char **split_f_str, int i, t_game **game)
{
    int     fd;
    int     pos;
    char    *f_name;
    // int     pxl_data[3]; // TODO: uncomment later
    int     len;

    f_name = split_f_str[i + 1];
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
    if (ft_strncmp(split_f_str[i], "NO", 2) == 0) pos = 0;
    else if (ft_strncmp(split_f_str[i], "SO", 2) == 0) pos = 1;
    else if (ft_strncmp(split_f_str[i], "EA", 2) == 0) pos = 2;
    else if (ft_strncmp(split_f_str[i], "WE", 2) == 0) pos = 3;
    else return (-1);
    (*game)->tex_paths[pos] = ft_strdup(f_name);
    // (*game)->textures[pos].img = mlx_xpm_file_to_image((*game)->mlx_ptr, 
    //     f_name, &(*game)->textures[pos].width, &(*game)->textures[pos].height); // TODO: uncomment later
    // if (!(*game)->textures[pos].img)
    // {
    //     printf("Error: MLX failed to load texture: %s\n", f_name);
    //     return (-1);
    // }
    // (*game)->textures[pos].addr = mlx_get_data_addr((*game)->textures[pos].img, 
    //     &pxl_data[0], &pxl_data[1], &pxl_data[2]);
    
    return (0);
}

// NO -> 0, SO -> 1, EA -> 2, WE -> 3
int	check_asset_tex(char *f_str, t_game **game) // f_str here contains the full line from the .cub file
{
	// int		fd;
	int		i;
	char	**split_f_str;
	// char	*tmp;

	i = 0;
	split_f_str = ft_split(f_str, ' ');
	while (split_f_str[i])
	{
		if (ft_strncmp(split_f_str[i], "NO", 2) == 0 
			|| ft_strncmp(split_f_str[i], "SO", 2) == 0
			|| ft_strncmp(split_f_str[i], "EA", 2) == 0
			|| ft_strncmp(split_f_str[i], "WE", 2) == 0)
		{
			printf("found a texture %s : %s\n", split_f_str[i], split_f_str[i + 1]);
			// tmp = split_f_str[i + 1];
			// if (tmp && ft_strncmp(tmp, "./", 2) == 0)
			// {
			// 	printf("found the ./\n");
			// 	split_f_str[i + 1] = ft_strdup(split_f_str[i + 1] + 2); // remove the ./
			// 	if (!split_f_str[i + 1])
			// 		return (free_array(split_f_str), -1);
			// 	free(tmp);
			// 	printf("final text file is %s")
			// }
			if (save_texture(split_f_str, i, game) != 0)
				return (free_array(split_f_str), -1);
			break ;
		}
		i++;
	}
	return (0);
}
