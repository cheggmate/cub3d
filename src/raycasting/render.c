/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotong <jotong@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:23:30 by jotong            #+#    #+#             */
/*   Updated: 2026/04/24 21:00:13 by jotong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int colour)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	if (!game->img.addr)
		return ;
	dst = game->img.addr + (y * game->img.line_length
			+ x * (game->img.bpp / 8));
	*(unsigned int *)dst = colour;
}

t_texture	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->textures[3]);
		return (&game->textures[2]);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (&game->textures[1]);
		return (&game->textures[0]);
	}
}

static unsigned int	add_shade(char *colour_ptr, t_ray *ray)
{
	unsigned int	colour;
	double			shadow;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	colour = *(unsigned int *)colour_ptr;
	if (ray->side == 1)
		colour = (colour >> 1) & 8355711;
	shadow = 1.0 / (1.0 + ray->wall_dist * 0.05);
	r = (colour >> 16) & 0xFF;
	g = (colour >> 8) & 0xFF;
	b = colour & 0xFF;
	r = (unsigned int)(r * shadow);
	g = (unsigned int)(g * shadow);
	b = (unsigned int)(b * shadow);
	return ((r << 16) | (g << 8) | b);
}

int	get_texture_pixel(t_game *game, t_ray *ray, int y, int line_h)
{
	t_texture	*tex;
	int			tex_y;
	double		step;
	double		tex_pos;
	char		*colour_ptr;

	tex = select_texture(game, ray);
	step = 1.0 * tex->height / line_h;
	tex_pos = ((double)y - (double)HEIGHT / 2 + (double)line_h / 2) * step;
	tex_y = (int)tex_pos % tex->height;
	if (tex_y < 0)
		tex_y = 0;
	colour_ptr = tex->addr + (tex_y * tex->line_len
			+ ray->tex_x * (tex->bpp / 8));
	return (add_shade(colour_ptr, ray));
}
