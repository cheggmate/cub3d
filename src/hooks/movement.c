/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 10:14:08 by jotong            #+#    #+#             */
/*   Updated: 2026/04/28 00:56:30 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_pos(t_player *p, char **grid, double dx, double dy)
{
	if (grid[(int)p->pos_y][(int)(p->pos_x + dx)] != '1')
		p->pos_x += dx;
	if (grid[(int)(p->pos_y + dy)][(int)p->pos_x] != '1')
		p->pos_y += dy;
}

int	move_player(t_game *game)
{
	double		s;
	t_player	*p;
	char		**grid;

	s = 0.1;
	p = &game->player;
	grid = game->map->grid;
	if (p->move_up)
		update_pos(p, grid, p->dir_x * s, p->dir_y * s);
	if (p->move_down)
		update_pos(p, grid, -p->dir_x * s, -p->dir_y * s);
	if (p->move_left)
		update_pos(p, grid, -p->plane_x * s, -p->plane_y * s);
	if (p->move_right)
		update_pos(p, grid, p->plane_x * s, p->plane_y * s);
	return (0);
}

int	key_press(int keycode, void *game_in)
{
	t_game	*game;

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
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 1;
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
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 0;
	return (0);
}
