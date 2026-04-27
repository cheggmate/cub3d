/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:31:52 by jotong            #+#    #+#             */
/*   Updated: 2026/04/28 01:32:17 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	line_buffer[MAX_LINE];
	int			i;
	ssize_t		bytes_read;
	char		c;

	if (fd < 0 || fd > 1023 || MAX_LINE <= 0)
		return (NULL);
	i = 0;
	while (i < MAX_LINE - 1)
	{
		bytes_read = read(fd, &c, 1);
		if (bytes_read <= 0)
		{
			if (i == 0)
				return (NULL);
			break ;
		}
		line_buffer[i++] = c;
		if (c == '\n')
			break ;
	}
	line_buffer[i] = '\0';
	return (line_buffer);
}
