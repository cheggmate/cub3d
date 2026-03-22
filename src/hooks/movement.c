/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:14:08 by jotong            #+#    #+#             */
/*   Updated: 2026/03/22 10:13:12 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// movement.c: Logic for updating player coordinates (W, A, S, D).

#include "cub3d.h"

int	move_player(t_game **game, double move_x, double move_y)
{
	double	padding;

	padding = 0.1; // buffer so that the player doesnt get too close to the wall
	if (move_x > 0)
		padding = 0.1;
	else
		padding = -0.1;
	if ((*game)->map->grid[(int)(*game)->player.pos_y][(int)((*game)->player.pos_x + move_x + padding)] != '1')
		(*game)->player.pos_x += move_x;
	if ((*game)->map->grid[(int)((*game)->player.pos_y + move_y + padding)][(int)(*game)->player.pos_x] != '1')
		(*game)->player.pos_y += move_y;
	return (0);
}

int	key_press(int keycode, void *game_in)
{
	t_game	*game;

	game = (t_game *)game_in;
	if (keycode == KEY_ESC)
	{
		free_and_exit(&game, 0, "Completed");
		close_window(game);
	}
	else if (keycode == KEY_W)
		game->player.move_up = 1;
	else if (keycode == KEY_A)
		game->player.move_left = 1;
	else if (keycode == KEY_S)
		game->player.move_down = 1;
	else if (keycode == KEY_D)
		game->player.move_right = 1;
	return (0);
}

int	key_release(int keycode, void *game_in)
{
	t_game	*game;

	game = (t_game *)game_in;
	if (keycode == KEY_W)
		game->player.move_up = 0;
	else if (keycode == KEY_A)
		game->player.move_left = 0;
	else if (keycode == KEY_S)
		game->player.move_down = 0;
	else if (keycode == KEY_D)
		game->player.move_right = 0;
	return (0);
}
