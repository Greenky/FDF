/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:03:55 by vmazurok          #+#    #+#             */
/*   Updated: 2018/01/12 19:04:01 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <errno.h>

typedef struct	s_point
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}				t_point;

typedef struct	s_grafx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		scr_size;
	int		img_w;
	int		img_h;
	int		img_d;
	t_point *map;
	t_point centre;
	float	ang_y;
	float	ang_x;
	float	ang_z;
	int		x_shift;
	int		y_shift;
	float	scale;
}				t_grafx;

unsigned int	grad(t_point point1, t_point point2, float x, char c);
void			line_draw(t_point p1, t_point p2, t_grafx *cub);
t_point			shift(t_point point, t_grafx *gfx);
t_point			rot(t_point p, t_grafx *gfx, char c);
void			scaling(t_grafx *gfx, float scale_ch, int b);
void			key_hendler(int key, t_grafx *gfx);
void			map_draw(t_grafx *gfx);
unsigned int	color_find(char *line, int n);
int				move_handle(int key, void *g);
void			pixel_add(t_grafx *gfx, int x, int y, unsigned int color);

#endif
