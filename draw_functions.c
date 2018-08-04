/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:00:02 by vmazurok          #+#    #+#             */
/*   Updated: 2018/01/23 19:00:05 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void			scaling(t_grafx *g, float scale_ch, int b)
{
	int i;

	i = -1;
	if (!b)
		while (++i < (g->img_w * g->img_h))
		{
			g->map[i].x = (g->map[i].x - (g->centre.x - g->img_w / 2 *
			g->scale)) * scale_ch + g->centre.x - g->img_w / 2 * scale_ch *
			g->scale;
			g->map[i].y = (g->map[i].y - (g->centre.y - g->img_h / 2 *
			g->scale)) * scale_ch + g->centre.y - g->img_h / 2 * scale_ch *
			g->scale;
			g->map[i].z = g->map[i].z * scale_ch;
		}
	else
		while (++i < (g->img_w * g->img_h))
		{
			g->map[i].x = g->map[i].x * scale_ch + g->centre.x -
			g->img_w / 2 * scale_ch;
			g->map[i].y = g->map[i].y * scale_ch + g->centre.y -
			g->img_h / 2 * scale_ch;
			g->map[i].z = g->map[i].z * scale_ch;
		}
	g->scale *= scale_ch;
}

unsigned int	grad(t_point p1, t_point p2, float x, char c)
{
	unsigned int color;

	color = p1.color;
	if (c == 'x')
	{
		color += (long)(((long)(p2.color % 256) - (long)(p1.color
		% 256)) / fabs(p2.x - p1.x) * fabs(x - p1.x));
		color += (long)(((long)((p2.color / 256) % 256) - (long)((p1.color /
		256) % 256)) / fabs(p2.x - p1.x) * fabs(x - p1.x)) * 256;
		color += (long)(((long)((p2.color / 256 / 256) % 256) -
		(long)((p1.color / 256 / 256) % 256)) / fabs(p2.x - p1.x) *
		fabs(x - p1.x)) * 256 * 256;
		return (color);
	}
	else
	{
		color += (long)(((long)(p2.color % 256) - (long)(p1.color % 256)) /
		fabs(p2.y - p1.y) * fabs(x - p1.y));
		color += (long)(((long)((p2.color / 256) % 256) - (long)((p1.color /
		256) % 256)) / fabs(p2.y - p1.y) * fabs(x - p1.y)) * 256;
		color += (long)(((long)((p2.color / 256 / 256) % 256) -
		(long)((p1.color / 256 / 256) % 256)) / fabs(p2.y - p1.y) *
		fabs(x - p1.y)) * 256 * 256;
		return (color);
	}
}

void			line_draw(t_point p1, t_point p2, t_grafx *gfx)
{
	float	x;
	float	y;

	x = p1.x;
	y = p1.y;
	mlx_pixel_put(gfx->mlx, gfx->win, x, y, p1.color);
	if (fabs(p1.x - p2.x) > fabs(p1.y - p2.y))
		while (p1.x > p2.x ? x > p2.x : x < p2.x)
		{
			x > p2.x ? x-- : x++;
			y = (int)(((x - p1.x) / (p2.x - p1.x)) * (p2.y - p1.y) + p1.y);
			mlx_pixel_put(gfx->mlx, gfx->win, x, y, grad(p1, p2, x, 'x'));
		}
	else
		while (p1.y > p2.y ? y > p2.y : y < p2.y)
		{
			y > p2.y ? y-- : y++;
			x = (int)(((y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y)) + p1.x);
			mlx_pixel_put(gfx->mlx, gfx->win, x, y, grad(p1, p2, y, 'y'));
		}
}

t_point			shift(t_point point, t_grafx *gfx)
{
	point.x += gfx->x_shift;
	point.y += gfx->y_shift;
	return (point);
}

t_point			rot(t_point p, t_grafx *gfx, char c)
{
	t_point new_p;

	new_p = p;
	if (c == 'z')
	{
		new_p.x = round((p.x - gfx->centre.x) * cos(gfx->ang_z) -
		(p.y - gfx->centre.y) * sin(gfx->ang_z) + gfx->centre.x);
		new_p.y = round((p.x - gfx->centre.x) * sin(gfx->ang_z) +
		(p.y - gfx->centre.y) * cos(gfx->ang_z) + gfx->centre.y);
	}
	else if (c == 'x')
	{
		new_p.y = round((p.y - gfx->centre.y) * cos(gfx->ang_x) -
		(p.z - gfx->centre.z) * sin(gfx->ang_x) + gfx->centre.y);
		new_p.z = round((p.y - gfx->centre.y) * sin(gfx->ang_x) +
		(p.z - gfx->centre.z) * cos(gfx->ang_x) + gfx->centre.z);
	}
	else
	{
		new_p.x = (p.x - gfx->centre.x) * cos(gfx->ang_y) +
		(p.z - gfx->centre.z) * sin(gfx->ang_y) + gfx->centre.x;
		new_p.z = (-1) * (p.x - gfx->centre.x) * sin(gfx->ang_y) +
		(p.z - gfx->centre.z) * cos(gfx->ang_y) + gfx->centre.z;
	}
	return (new_p);
}
