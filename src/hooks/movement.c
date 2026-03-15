/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:14:08 by jotong            #+#    #+#             */
/*   Updated: 2026/03/15 16:34:50 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// movement.c: Logic for updating player coordinates (W, A, S, D).

#include "cub3d.h"

int move_player(t_game **game, double move_x, double move_y)
{
    // Simple collision detection: check if the next position is a '0'
    if ((*game)->map->grid[(int)(*game)->player.pos_y][(int)((*game)->player.pos_x + move_x)] == '0')
        (*game)->player.pos_x += move_x;
    if ((*game)->map->grid[(int)((*game)->player.pos_y + move_y)][(int)(*game)->player.pos_x] == '0')
        (*game)->player.pos_y += move_y;
    return (0);
}
