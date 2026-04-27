/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:29:46 by jotong            #+#    #+#             */
/*   Updated: 2026/04/28 00:22:55 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static int	parse_rgb(char *str, int *rgb)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split || char_arr_size(split) != 3)
	{
		free_array(split);
		return (-1);
	}
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		if (!arr_in_limit(rgb[i], 0, 255))
		{
			free_array(split);
			return (-1);
		}
		i++;
	}
	free_array(split);
	return (0);
}

int	save_colour(char **split_f_str, int i, t_game **game)
{
	int	rgb[3];
	int	colour_val;

	if (parse_rgb(split_f_str[i + 1], rgb) == -1)
		return (-1);
	colour_val = rgb_to_int(rgb[0], rgb[1], rgb[2]);
	if (ft_strncmp(split_f_str[0], "F", 2) == 0)
	{
		if ((*game)->floor_colour != -1)
			return (-1);
		(*game)->floor_colour = colour_val;
	}
	else if (ft_strncmp(split_f_str[0], "C", 2) == 0)
	{
		if ((*game)->ceiling_colour != -1)
			return (-1);
		(*game)->ceiling_colour = colour_val;
	}
	else
		return (-1);
	return (0);
}

int	check_asset_colour(char *f_str, t_game **game)
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
	if (char_arr_size(split_f_str))
	{
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
	}
	free_array(split_f_str);
	return (0);
}
