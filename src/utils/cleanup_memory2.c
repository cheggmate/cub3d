/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_memory2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:51:38 by jotong            #+#    #+#             */
/*   Updated: 2026/03/26 14:16:10 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_file(int fd)
{
	if (fd > 2)
		close(fd);
	printf("done closing file\n");
}

void	free_safely(char **line)
{
	if (!(*line))
		return;
	free((*line));
	(*line) = NULL;
}
