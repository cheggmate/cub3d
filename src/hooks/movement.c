/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:14:08 by jotong            #+#    #+#             */
/*   Updated: 2026/02/22 10:14:16 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// movement.c: Logic for updating player coordinates (W, A, S, D).

#include "cub3d.h"

int move_player(t_data *data, double move_x, double move_y)
{
    // Simple collision detection: check if the next position is a '0'
    if (data->map[(int)data->player.pos_y][(int)(data->player.pos_x + move_x)] == '0')
        data->player.pos_x += move_x;
    if (data->map[(int)(data->player.pos_y + move_y)][(int)data->player.pos_x] == '0')
        data->player.pos_y += move_y;
    return (0);
}
