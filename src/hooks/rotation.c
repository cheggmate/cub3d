#include "cub3d.h"

void rotate_player(t_game *game, double speed)
{
    t_player *p;
    double old_dir_x;
    double old_plane_x;

    p = &game->player;
    old_dir_x = p->dir_x;
    
    // Rotate direction vector
    p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
    p->dir_y = old_dir_x * sin(speed) + p->dir_y * cos(speed);
    
    // Rotate camera plane (must stay perpendicular to direction)
    old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cos(speed) - p->plane_y * sin(speed);
    p->plane_y = old_plane_x * sin(speed) + p->plane_y * cos(speed);
}

int handle_rotation(t_game *game)
{
    double rot_speed;

    rot_speed = 0.05; // Adjust for sensitivity
    if (game->player.rotate_left)
        rotate_player(game, -rot_speed);
    if (game->player.rotate_right)
        rotate_player(game, rot_speed);
    return (0);
}