/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:04:50 by vordynsk          #+#    #+#             */
/*   Updated: 2018/04/18 18:04:53 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init(t_general *gen)
{
	gen->fd = 0;
	gen->i = 0;
	gen->j = 0;
	gen->line_buff = NULL;
	gen->len = 0;
	gen->rows = 0;
	gen->len_buff = 0;
	gen->n = 0;
	gen->size_x = 1000;
	gen->size_y = 1000;
	gen->scale_x = 1;
	gen->scale_y = 1;
	gen->scale_z = 1;
	gen->image = NULL;
	gen->bpp = 0;
	gen->ed = 0;
	gen->val = 0;
	gen->x0 = 0;
	gen->y0 = 0;
	gen->x1 = 0;
	gen->y1 = 0;
	gen->k = 0;
	gen->b = 0;
	gen->dx = 0;
	gen->dy = 0;
}

t_point	init_point(double x, double y, double z, t_color color)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return (point);
}

void	ft_center(t_general *gen)
{
	gen->center.x = (gen->size_x - 49) / 2;
	gen->center.y = (gen->size_y - 80) / 2;
}

void	ft_winsize(t_general *gen)
{
	if (gen->len <= 20)
	{
		gen->scale_x = 100;
		gen->size_x = gen->len * 100;
	}
	else
	{
		gen->scale_x = 10;
		gen->size_x = gen->len * 10;
	}
	if (gen->rows <= 20)
	{
		gen->scale_y = 100;
		gen->size_y = gen->rows * 100;
	}
	else
	{
		gen->scale_y = 10;
		gen->size_y = gen->rows * 10;
	}
}
