/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:45:58 by vmazurok          #+#    #+#             */
/*   Updated: 2018/01/24 16:46:00 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void			key_hendler(int key, t_grafx *gfx)
{
	if (key == 123)
		gfx->ang_y -= 0.05;
	else if (key == 124)
		gfx->ang_y += 0.05;
	else if (key == 126)
		gfx->ang_x += 0.05;
	else if (key == 125)
		gfx->ang_x -= 0.05;
	else if (key == 12)
		gfx->ang_z += 0.05;
	else if (key == 14)
		gfx->ang_z -= 0.05;
	else if (key == 0)
		gfx->x_shift -= 5;
	else if (key == 2)
		gfx->x_shift += 5;
	else if (key == 13)
		gfx->y_shift -= 5;
	else if (key == 1)
		gfx->y_shift += 5;
	else if (key == 36)
		scaling(gfx, 1.1, 0);
	else if (key == 51)
		scaling(gfx, 0.9, 0);
}

void			clear_map(t_grafx *gfx)
{
	int		bpp;
	int		size_l;
	int		end;
	char	*buff;

	buff = mlx_get_data_addr(gfx->img, &bpp, &size_l, &end);
	ft_bzero(buff, gfx->scr_size * gfx->scr_size * 4);
}

void			map_draw(t_grafx *g)
{
	int x;
	int y;

	y = -1;
	mlx_clear_window(g->mlx, g->win);
	while (++y < g->img_h && (x = -1))
		while (++x < g->img_w)
		{
			if (x + 1 < g->img_w)
				line_draw(shift(rot(rot(rot(g->map[g->img_w * y + x + 1],
				g, 'x'), g, 'y'), g, 'z'), g), shift(rot(rot(rot(
				g->map[g->img_w * y + x], g, 'x'), g, 'y'), g, 'z'), g), g);
			if (x - 1 >= 0)
				line_draw(shift(rot(rot(rot(g->map[g->img_w * y + x - 1],
				g, 'x'), g, 'y'), g, 'z'), g), shift(rot(rot(rot(
				g->map[g->img_w * y + x], g, 'x'), g, 'y'), g, 'z'), g), g);
			if (y + 1 < g->img_h)
				line_draw(shift(rot(rot(rot(g->map[g->img_w * (y + 1) + x],
				g, 'x'), g, 'y'), g, 'z'), g), shift(rot(rot(rot(
				g->map[g->img_w * y + x], g, 'x'), g, 'y'), g, 'z'), g), g);
			if (y - 1 >= 0)
				line_draw(shift(rot(rot(rot(g->map[g->img_w * (y - 1) + x],
				g, 'x'), g, 'y'), g, 'z'), g), shift(rot(rot(rot(
				g->map[g->img_w * y + x], g, 'x'), g, 'y'), g, 'z'), g), g);
		}
}

unsigned int	color_find(char *line, int n)
{
	int				i;
	unsigned int	num;
	const char		base[16] = "0123456789ABCDEF";

	while (line[n] && line[n] >= '0' && line[n] <= '9')
		n++;
	if (line[n] && line[n] == ',')
	{
		n += 2;
		num = 0;
		while (line[++n] && line[n] != ' ')
		{
			i = 0;
			while (base[i] && base[i] != ft_toupper(line[n]))
				i++;
			if (!base[i])
				return (0x00FFFFFF);
			else
				num = num * 16 + i;
		}
	}
	else
		return (0x00FFFFFF);
	return (num);
}

int				move_handle(int key, void *g)
{
	t_grafx *gfx;

	gfx = (t_grafx *)g;
	if (key == 53)
	{
		free(gfx->map);
		free(gfx);
		exit(1);
	}
	key_hendler(key, gfx);
	map_draw(gfx);
	return (0);
}
