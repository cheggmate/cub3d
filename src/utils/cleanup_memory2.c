/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_memory2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:38 by jotong            #+#    #+#             */
/*   Updated: 2026/04/24 21:33:22 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_file(int fd)
{
	if (fd > 2)
		close(fd);
}

void	free_checked(int **checked, int height)
{
	int	i;

	if (!checked)
		return ;
	i = 0;
	while (i < height)
	{
		if (checked[i])
			free(checked[i]);
		i++;
	}
	free(checked);
}
