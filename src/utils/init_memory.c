/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:34:34 by jotong            #+#    #+#             */
/*   Updated: 2026/02/22 14:43:24 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

// t_pool	*init_mem_pool(size_t size)
// {
// 	t_pool	*mem_p;

// 	mem_p = ft_calloc(1, sizeof(t_pool));
// 	if (!mem_p)
// 	{
// 		ft_printf("Error\nFailed to initialise mem_p\n");
// 		return (NULL);
// 	}
// 	mem_p->head = ft_calloc(size, sizeof(char));
// 	if (!mem_p->head)
// 	{
// 		ft_printf("Error\nFailed to initialise mem_p->head\n");
// 		return (NULL);
// 	}
// 	mem_p->total = size;
// 	mem_p->used = 0;
// 	return (mem_p);
// }

// void	*alloc_mem(t_pool *mem_p, size_t size)
// {
// 	void	*sub_pool;

// 	sub_pool = NULL;
// 	if (!mem_p || !mem_p->head)
// 		return (NULL);
// 	if (mem_p->used + size > mem_p->total)
// 	{
// 		ft_printf("Error\nMem overflow\n");
// 		return (NULL);
// 	}
// 	sub_pool = mem_p->head + mem_p->used;
// 	mem_p->used += size;
// 	return (sub_pool);
// }
