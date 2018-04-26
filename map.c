/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:06:59 by vordynsk          #+#    #+#             */
/*   Updated: 2018/04/18 18:07:01 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		count(t_general *gen, char *filename)
{
	if ((gen->fd = open(filename, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(gen->fd, &gen->line) > 0)
	{
		gen->len_buff = 0;
		gen->i = 0;
		gen->buff = ft_strsplit(gen->line, ' ');
		while (gen->buff[gen->i] != NULL)
		{
			if (ft_isnumber(gen->buff[gen->i]) == 1)
				gen->len_buff++;
			gen->i++;
		}
		if (gen->len == 0 || gen->len == gen->len_buff)
			gen->len = gen->len_buff;
		else if (gen->len_buff != 0 && gen->len != gen->len_buff)
			return (0);
		if (gen->line != NULL)
			gen->rows++;
		ft_strdel(&gen->line);
		ft_chararrdel(gen->buff, &gen->buff);
	}
	close(gen->fd);
	return (1);
}

void	ft_map(t_general *gen, char *filename)
{
	gen->i = 0;
	gen->fd = open(filename, O_RDONLY);
	ft_scale(gen);
	gen->points = (t_point *)malloc(sizeof(t_point) * gen->rows * gen->len);
	while (get_next_line(gen->fd, &gen->line) > 0)
	{
		gen->buff = ft_strsplit(gen->line, ' ');
		gen->j = 0;
		gen->m = 0;
		while (gen->buff[gen->m] != NULL && gen->i < (gen->len * gen->rows))
		{
			gen->points[gen->i] = init_point(gen->j * gen->scale_x, gen->n *
			gen->scale_y, ft_atoi(gen->buff[gen->m]) * gen->scale_z,
			gen->color);
			gen->i++;
			gen->j++;
			gen->m++;
		}
		ft_strdel(&gen->line);
		ft_chararrdel(gen->buff, &gen->buff);
		gen->n++;
	}
}

void	ft_screen_stuff(t_general *gen)
{
	char	*color;
	char	*buff;

	color = ft_strnew(6);
	mlx_clear_window(gen->init, gen->win);
	ft_clearscr(gen);
	ft_line(gen);
	mlx_put_image_to_window(gen->init, gen->win, gen->img, 49, 80);
	buff = ft_itoa_base(gen->color.channel[0], 16);
	ft_strcpy(color, buff);
	ft_strdel(&buff);
	buff = ft_itoa_base(gen->color.channel[1], 16);
	color = ft_strcat(color, buff);
	ft_strdel(&buff);
	buff = ft_itoa_base(gen->color.channel[2], 16);
	color = ft_strcat(color, buff);
	ft_strdel(&buff);
	mlx_string_put(gen->init, gen->win, 10, 50, 0xFFFFFF, color);
	mlx_string_put(gen->init, gen->win, 10, 10, 0xFFFFFF, "1 and 2 +/- blue;\
	3 and 4 +/- green; 5 and 6 +/- red; 7 - reset to white");
	mlx_string_put(gen->init, gen->win, 10, 30, 0xFFFFFF, "use arrows to \
	rotate, i and o to zoom in and out, w s a d to move along y and x axis");
	ft_strdel(&color);
}

void	ft_move(t_general *gen, int key)
{
	int		i;

	i = 0;
	while (i < gen->len * gen->rows)
	{
		if (key == 13)
			gen->points[i].y += 50;
		else if (key == 1)
			gen->points[i].y -= 50;
		else if (key == 2)
			gen->points[i].x -= 50;
		else if (key == 0)
			gen->points[i].x += 50;
		i++;
	}
}

void	ft_short_lines(t_general *gen, int l)
{
	if (l == 0)
	{
		put_pixel(gen, gen->x0, gen->y0, gen->color);
		gen->y0 = gen->k * gen->x0++ + gen->b;
	}
	else if (l == 1)
	{
		put_pixel(gen, gen->x0, gen->y0, gen->color);
		gen->x0 = (gen->y0++ - gen->b) / gen->k;
	}
}
