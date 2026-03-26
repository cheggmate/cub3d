/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:29:46 by jotong            #+#    #+#             */
/*   Updated: 2026/03/26 23:07:40 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Extracts and validates the F and C RGB values.
#include "cub3d.h"
#include "libft.h"

static int rgb_to_int(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int	save_colour(char **split_f_str, int i, t_game **game) // the i position of the split_f_str array contains the full RGB
{
	char	**colour; //rgb as provided in cub
	int		i_colour[3];

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
	if (ft_strncmp(split_f_str[0], "F" , 2) == 0)
	{
		(*game)->floor_colour = rgb_to_int(i_colour[0], i_colour[1], i_colour[2]);
		return (free_array(colour), 0);
	}
	else if (ft_strncmp(split_f_str[0], "C" , 2) == 0)
	{
		(*game)->ceiling_colour = rgb_to_int(i_colour[0], i_colour[1], i_colour[2]);
		return (free_array(colour), 0);
	}
	return (free_array(colour), -1); // unknown colour
}

int	check_asset_colour(char *f_str, t_game **game) // f_str here contains the full line from the .cub file
{
	int		i;
	char	**split_f_str;

	i = 0;
	split_f_str = ft_split(f_str, ' ');
	while (split_f_str[i])
	{
		if (ft_strncmp(split_f_str[i], "F", 1) == 0
				|| ft_strncmp(split_f_str[i], "C", 1) == 0)
		{
			if (save_colour(split_f_str, i, game) != 0)
				return (free_array(split_f_str), -1);
			break ;
		}
		i++;
	}
	// printf("successfully read the colour %s,\n", split_f_str[1]);
	free_array(split_f_str);
	return (0);
}
