/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:45:28 by vmazurok          #+#    #+#             */
/*   Updated: 2018/01/24 16:45:31 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		filling(int fd, t_grafx *g, char *line, int n)
{
	int		x;
	int		y;

	y = 0;
	while (get_next_line(fd, &line) && line[0])
	{
		n = 0;
		x = 0;
		while (line[n])
		{
			while (line[n] && line[n] == ' ')
				n++;
			if (line[n] && line[n] != ' ')
			{
				g->map[g->img_w * y + x].color = color_find(line + n, 0);
				g->map[g->img_w * y + x].x = x;
				g->map[g->img_w * y + x].y = y;
				g->map[g->img_w * y + (x++)].z = ft_atoi(line + n);
			}
			while (line[n] && line[n] != ' ')
				n++;
		}
		y++;
		free(line);
	}
}

void		scale_finder(int *i, int *j, const int fd, t_grafx *gfx)
{
	char	*line;
	int		n;
	int		file;

	*j = 0;
	while ((file = get_next_line(fd, &line)) > 0 && *line)
	{
		(*j)++;
		n = 0;
		*i = 0;
		while (line[n])
		{
			while (line[n] && line[n] == ' ')
				n++;
			if (line[n] && line[n] != ' ')
			{
				(*i)++;
				gfx->img_d = fmax(gfx->img_d, ft_atoi(line + n));
			}
			while (line[n] && line[n] != ' ')
				n++;
		}
		free(line);
	}
	file < 0 ? exit((int)write(2, "Reading file error, sore\n", 25)) : file;
}

void		mapper(int fd, char *name, t_grafx *gfx)
{
	t_point	*map;

	scale_finder(&(gfx->img_w), &(gfx->img_h), fd, gfx);
	close(fd);
	fd = open(name, O_RDONLY);
	if ((map = (t_point *)ft_memalloc(sizeof(t_point) * gfx->img_h *
	gfx->img_w)) == NULL)
	{
		free(gfx);
		exit(1);
	}
	gfx->map = map;
	filling(fd, gfx, NULL, 0);
}

static void	put_params(t_grafx *gfx)
{
	gfx->scr_size = 1200;
	gfx->centre.x = gfx->scr_size / 2;
	gfx->centre.y = gfx->scr_size / 2 + 200;
	gfx->ang_x = -2.2;
	gfx->ang_y = -3.84;
	gfx->ang_z = 3;
	gfx->img_d = 0;
	gfx->scale = 1;
	if (!(gfx->mlx = mlx_init()))
	{
		free(gfx);
		exit((int)write(2, "mlx_init error\n", 15));
	}
	gfx->win = mlx_new_window(gfx->mlx, gfx->scr_size, gfx->scr_size, "FDF");
	if (!(gfx->win))
	{
		free(gfx);
		exit((int)write(2, "mlx_new_window error\n", 21));
	}
}

int			main(int argc, char **argv)
{
	t_grafx	*gfx;
	int		fd;

	if (argc < 2 || argc > 2)
		exit((int)write(2, "Usage :\n./fdf [filename]\n", 25));
	if ((fd = open(argv[1], O_RDONLY)) <= 0)
	{
		perror("Error");
		exit(1);
	}
	if ((gfx = (t_grafx *)ft_memalloc(sizeof(t_grafx))) == NULL)
		return (1);
	put_params(gfx);
	mapper(fd, argv[1], gfx);
	scaling(gfx, gfx->scr_size * 0.9 / sqrt(pow(gfx->img_h, 2) +
	pow(gfx->img_w, 2) + pow(gfx->img_d, 2)), 1);
	map_draw(gfx);
	mlx_hook(gfx->win, 2, (1L << 0), move_handle, (void *)gfx);
	mlx_loop(gfx->mlx);
	free(gfx->map);
	free(gfx);
	return (0);
}
