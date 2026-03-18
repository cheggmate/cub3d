/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tmp_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:50:41 by jotong            #+#    #+#             */
/*   Updated: 2026/03/18 16:36:11 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

t_list	*create_tmp_list(char *map_row)
{
	t_list	*tmp_list;
	char	*map_row_dup;

	map_row_dup = ft_strdup(map_row);
	if (!map_row_dup)
		return (NULL);
	tmp_list = ft_lstnew(map_row_dup);
	return (tmp_list);
}

int	add_row_to_list(t_list *list, char *map_row)
{
	char	*map_row_dup;

	if (!map_row)
		return (0);
	map_row_dup = ft_strdup(map_row);
	if (!map_row_dup)
		return (-1);
	if (!list)
	{
		list = create_tmp_list(map_row);
		if (!list)
			return (-1);
		return (0);
	}
	ft_lstadd_back(&list, ft_lstnew(map_row_dup));
	return (0);
}

