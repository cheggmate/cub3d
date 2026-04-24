/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tmp_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:50:41 by jotong            #+#    #+#             */
/*   Updated: 2026/04/24 20:30:31 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

t_list	*create_tmp_list(char *map_row)
{
	t_list	*tmp_list;
	char	*map_row_dup;
	int		row_len;

	row_len = ft_strlen(map_row);
	map_row_dup = ft_strdup(map_row);
	if (!map_row_dup)
		return (NULL);
	if (((char *)map_row_dup)[row_len - 1] == '\n')
		((char *)map_row_dup)[row_len - 1] = '\0';
	tmp_list = ft_lstnew(map_row_dup);
	return (tmp_list);
}

int	add_row_to_list(t_list **list, char *map_row)
{
	char	*map_row_dup;
	int		row_len;
	t_list	*new_node;

	row_len = ft_strlen(map_row);
	if (!map_row)
		return (0);
	if (!(*list))
	{
		(*list) = create_tmp_list(map_row);
		if (!(*list))
			return (-1);
		return (0);
	}
	map_row_dup = ft_strdup(map_row);
	if (((char *)map_row_dup)[row_len - 1] == '\n')
		((char *)map_row_dup)[row_len - 1] = '\0';
	if (!map_row_dup)
		return (-1);
	new_node = ft_lstnew(map_row_dup);
	if (!new_node)
		return (free(map_row_dup), -1);
	ft_lstadd_back(list, new_node);
	return (0);
}
