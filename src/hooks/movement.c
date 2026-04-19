/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:14:08 by jotong            #+#    #+#             */
/*   Updated: 2026/04/19 16:31:06 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// movement.c: Logic for updating player coordinates (W, A, S, D).

#include "cub3d.h"

int move_player(t_game **game)
{
    double s = 0.1; // speed
    t_player *p = &(*game)->player;
    char **grid = (*game)->map->grid;

    if (p->move_up)
    {
        if (grid[(int)p->pos_y][(int)(p->pos_x + p->dir_x * s)] != '1') p->pos_x += p->dir_x * s;
        if (grid[(int)(p->pos_y + p->dir_y * s)][(int)p->pos_x] != '1') p->pos_y += p->dir_y * s;
    }
    if (p->move_down)
    {
        if (grid[(int)p->pos_y][(int)(p->pos_x - p->dir_x * s)] != '1') p->pos_x -= p->dir_x * s;
        if (grid[(int)(p->pos_y - p->dir_y * s)][(int)p->pos_x] != '1') p->pos_y -= p->dir_y * s;
    }
    if (p->move_left) // Strafe Left: uses plane or perp dir
    {
        if (grid[(int)p->pos_y][(int)(p->pos_x - p->plane_x * s)] != '1') p->pos_x -= p->plane_x * s;
        if (grid[(int)(p->pos_y - p->plane_y * s)][(int)p->pos_x] != '1') p->pos_y -= p->plane_y * s;
    }
    if (p->move_right) // Strafe Right
    {
        if (grid[(int)p->pos_y][(int)(p->pos_x + p->plane_x * s)] != '1') p->pos_x += p->plane_x * s;
        if (grid[(int)(p->pos_y + p->plane_y * s)][(int)p->pos_x] != '1') p->pos_y += p->plane_y * s;
    }
    return (0);
}

int	key_press(int keycode, void *game_in)
{
	t_game	*game;

	printf("test key press\n");
	game = (t_game *)game_in;
	if (keycode == KEY_ESC)
		free_and_exit(&game, 0, "Completed");
	else if (keycode == KEY_W)
		game->player.move_up = 1;
	else if (keycode == KEY_A)
		game->player.move_left = 1;
	else if (keycode == KEY_S)
		game->player.move_down = 1;
	else if (keycode == KEY_D)
		game->player.move_right = 1;
	if (keycode == KEY_LEFT)
        game->player.rotate_left = 1;
    else if (keycode == KEY_RIGHT)
        game->player.rotate_right = 1;
	return (0);
}

int	key_release(int keycode, void *game_in)
{
	t_game	*game;

	printf("test key release\n");
	game = (t_game *)game_in;
	if (keycode == KEY_W)
		game->player.move_up = 0;
	else if (keycode == KEY_A)
		game->player.move_left = 0;
	else if (keycode == KEY_S)
		game->player.move_down = 0;
	else if (keycode == KEY_D)
		game->player.move_right = 0;
	if (keycode == KEY_LEFT)
        game->player.rotate_left = 0;
    else if (keycode == KEY_RIGHT)
        game->player.rotate_right = 0;
	return (0);
}
