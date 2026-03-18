/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:14:08 by jotong            #+#    #+#             */
/*   Updated: 2026/03/18 16:18:28 by jotong           ###   ########.fr       */
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

int	handle_keypress(int keycode, void *game_in)
{
	int		prev_x;
	int		prev_y;
	t_game	*game;

	game = (t_game *)game_in;
	prev_x = game->player.pos_x;
	prev_y = game->player.pos_y;
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
			|| keycode == KEY_D)
	{
		if (game->player.pos_x != prev_x || game->player.pos_y != prev_y)
			reload_map(&game, prev_x, prev_y);
	}
	return (0);
}
