/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:31:45 by vordynsk          #+#    #+#             */
/*   Updated: 2018/04/18 17:31:47 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_line(t_general *gen)
{
	int		i;

	i = 0;
	while (i < gen->len * gen->rows)
	{
		defline(gen, i, 0);
		if (coefline(gen) == 1)
			plotline(gen);
		defline(gen, i, 1);
		if (coefline(gen) == 1)
			plotline(gen);
		i++;
	}
}

int		defline(t_general *gen, int i, int l)
{
	if (l == 0)
	{
		if ((i + 1) % gen->len == 0)
			return (0);
		gen->color = gen->points[i].color;
		gen->x0 = gen->points[i].x;
		gen->y0 = gen->points[i].y;
		i++;
		gen->x1 = gen->points[i].x;
		gen->y1 = gen->points[i].y;
		return (1);
	}
	else
	{
		if (i >= (gen->rows * gen->len - gen->len))
			return (0);
		gen->color = gen->points[i].color;
		gen->x0 = gen->points[i].x;
		gen->y0 = gen->points[i].y;
		i = i + gen->len;
		gen->x1 = gen->points[i].x;
		gen->y1 = gen->points[i].y;
		return (1);
	}
}

int		coefline(t_general *gen)
{
	gen->dx = gen->x1 - gen->x0;
	gen->dy = gen->y1 - gen->y0;
	if (gen->dx == 0)
	{
		vertline(gen, gen->color);
		return (0);
	}
	gen->k = gen->dy / gen->dx;
	gen->b = gen->y0 - gen->k * gen->x0;
	return (1);
}

void	vertline(t_general *gen, t_color color)
{
	double	swap;

	if (gen->y0 > gen->y1)
	{
		swap = gen->y1;
		gen->y1 = gen->y0;
		gen->y0 = swap;
	}
	while (gen->y0 < gen->y1)
	{
		if (gen->x0 < 0 || gen->y0 < 0 || gen->x0 >= gen->size_x || gen->y0
		>= gen->size_y)
			return ;
		put_pixel(gen, (int)gen->x0, (int)gen->y0, color);
		gen->y0++;
	}
}

void	plotline(t_general *gen)
{
	if (gen->k >= -1 && gen->k <= 1)
	{
		if (gen->x0 > gen->x1)
			coordswap(gen);
		while (gen->x0 < gen->x1)
		{
			if (gen->x0 < 0 || gen->y0 < 0 || gen->x0 >= gen->size_x || gen->y0
			>= gen->size_y)
				return ;
			ft_short_lines(gen, 0);
		}
	}
	else
	{
		if (gen->y0 > gen->y1)
			coordswap(gen);
		while (gen->y0 < gen->y1)
		{
			if (gen->x0 < 0 || gen->y0 < 0 || gen->x0 >= gen->size_x || gen->y0
			>= gen->size_y)
				return ;
			ft_short_lines(gen, 1);
		}
	}
}
