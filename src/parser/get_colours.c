/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:29:46 by jotong            #+#    #+#             */
/*   Updated: 2026/04/29 16:17:50 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static int	is_digit(char *rgb_val)
{
	int		i;

	i = 0;
	while (rgb_val[i])
	{
		if (rgb_val[i] < '0' || rgb_val[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
static int	parse_rgb(char *str, int *rgb)
{
	char	**split;
	int		i;

	if (str[0] == ',' || str[ft_strlen(str) - 1] == ',')
		return (-1);
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
		if (!arr_in_limit(rgb[i], 0, 255) || !is_digit(split[i]))
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
	char	**s;

	i = 0;
	s = ft_split(f_str, ' ');
	if (!s || char_arr_size(s) != 2)
	{
		free_array(s);
		return (-1);
	}
	while (s[i])
	{
		if (ft_strncmp(s[i], "F", 1) == 0 || ft_strncmp(s[i], "C", 1) == 0)
		{
			if (save_colour(s, i, game) != 0)
			{
				free_array(s);
				return (-1);
			}
			break ;
		}
		i++;
	}
	free_array(s);
	return (0);
}
