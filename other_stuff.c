/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:09:23 by vordynsk          #+#    #+#             */
/*   Updated: 2018/04/18 18:09:24 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_scale(t_general *gen)
{
	int		screen;
	int		map;

	//gen->scale_x = gen->size_x / (gen->len);
	//gen->scale_y = gen->size_y / (gen->rows);
	if (gen->size_x > gen->size_y)
		screen = gen->size_y;
	else
		screen = gen->size_x;
	if (gen->len > gen->rows)
		map = gen->len;
	else
		map = gen->rows;
	gen->scale_z = screen / map;
}

void	turn(t_general *gen, double a, double b, double g)
{
	int		i;
	double	tmpx;
	double	tmpy;
	double	tmpz;

	i = 0;
	while (i < gen->len * gen->rows)
	{
		tmpx = gen->points[i].x - gen->center.x;
		tmpy = gen->points[i].y - gen->center.y;
		tmpz = gen->points[i].z;
		gen->points[i].x = tmpx * cos(b) * cos(g) + tmpz * sin(b) -
		tmpy * cos(b) * sin(g);
		gen->points[i].y = -tmpz * cos(b) * sin(a) + tmpx * (cos(g) *
		sin(a) * sin(b) + cos(a) * sin(g)) + tmpy * (cos(a) * cos(g) -
		sin(a) * sin(b) * sin(g));
		gen->points[i].z = tmpz * cos(a) * cos(b) + tmpx * (sin(a) *
		sin(g) - cos(a) * cos(g) * sin(b)) + tmpy * (cos(g) * sin(a) +
		cos(a) * sin(b) * sin(g));
		gen->points[i].x += gen->center.x;
		gen->points[i].y += gen->center.y;
		i++;
	}
}

void	coordswap(t_general *gen)
{
	double	x;
	double	y;

	x = gen->x0;
	y = gen->y0;
	gen->x0 = gen->x1;
	gen->y0 = gen->y1;
	gen->x1 = x;
	gen->y1 = y;
}

void	ft_zoom(t_general *gen, int key)
{
	gen->i = 0;
	while (gen->i < gen->len * gen->rows)
	{
		gen->points[gen->i].x -= gen->center.x;
		gen->points[gen->i].y -= gen->center.y;
		if (key == 34)
		{
			gen->points[gen->i].x *= 1.1;
			gen->points[gen->i].y *= 1.1;
			gen->points[gen->i].z *= 1.1;
		}
		else if (key == 31)
		{
			gen->points[gen->i].x /= 1.1;
			gen->points[gen->i].y /= 1.1;
			gen->points[gen->i].z /= 1.1;
		}
		else
			return ;
		gen->points[gen->i].x += gen->center.x;
		gen->points[gen->i].y += gen->center.y;
		gen->i++;
	}
	gen->i = 0;
}

void	color_change(t_general *gen, int key)
{
	gen->i = 0;
	while (gen->i < gen->len * gen->rows)
	{
		if (key == 18)
			gen->points[gen->i].color.channel[0] += 1;
		else if (key == 19)
			gen->points[gen->i].color.channel[0] -= 1;
		else if (key == 20)
			gen->points[gen->i].color.channel[1] += 1;
		else if (key == 21)
			gen->points[gen->i].color.channel[1] -= 1;
		else if (key == 23)
			gen->points[gen->i].color.channel[2] += 1;
		else if (key == 22)
			gen->points[gen->i].color.channel[2] -= 1;
		else if (key == 26)
			gen->points[gen->i].color.color = 0xFFFFFF;
		else
			return ;
		gen->i++;
	}
	gen->i = 0;
}
