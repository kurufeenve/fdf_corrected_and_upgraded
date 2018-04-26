/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:48:22 by vordynsk          #+#    #+#             */
/*   Updated: 2018/04/17 11:48:26 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_general	gen;

	init(&gen);
	gen.line = NULL;
	if (argc != 2 || count(&gen, argv[1]) == 0)
	{
		ft_putstr("map error\n");
		return (0);
	}
	gen.color.color = 0xFFFFFF;
	ft_winsize(&gen);
	ft_map(&gen, argv[1]);
	if ((gen.init = mlx_init()) == NULL ||
		(gen.win = mlx_new_window(gen.init,
		gen.size_x, gen.size_y, argv[1])) == NULL || (gen.img =
		mlx_new_image(gen.init, gen.size_x, gen.size_y)) == NULL ||
		(gen.image = mlx_get_data_addr(gen.img, &gen.bpp, &gen.val,
		&gen.ed)) == NULL)
		return (0);
	ft_screen_stuff(&gen);
	ft_center(&gen);
	mlx_hook(gen.win, 2, 5, key_hook, &gen);
	mlx_hook(gen.win, 17, 1L << 17, exit_x, NULL);
	mlx_loop(gen.init);
	return (0);
}

void	put_pixel(t_general *gen, int x, int y, t_color color)
{
	gen->image[y * gen->val + 4 * x] = color.channel[0];
	gen->image[y * gen->val + 4 * x + 1] = color.channel[1];
	gen->image[y * gen->val + 4 * x + 2] = color.channel[2];
}

int		exit_x(void)
{
	system("leaks fdf"); //
	exit(1);
}

int		key_hook(int key, void *ptr)
{
	t_general	*gen;

	gen = ptr;
	if (ptr == NULL)
		return (0);
	if (key == 126)
		turn(ptr, 0.087266462599716, 0, 0);
	else if (key == 125)
		turn(ptr, -0.087266462599716, 0, 0);
	else if (key == 124)
		turn(ptr, 0, 0.087266462599716, 0);
	else if (key == 123)
		turn(ptr, 0, -0.087266462599716, 0);
	else if (key == 34 || key == 31)
		ft_zoom(ptr, key);
	else if ((key > 17 && key < 24) || key == 26)
		color_change(ptr, key);
	else if (key == 13 || (key >= 0 && key <= 2))
		ft_move(gen, key);
	else if (key == 53)
	{
		system("leaks fdf"); //
		exit(0);
	}
	ft_screen_stuff(gen);
	return (0);
}

void	ft_clearscr(t_general *gen)
{
	int		i;

	i = 0;
	while (i < gen->size_x * gen->size_y * 4)
	{
		gen->image[i] = '\0';
		i++;
	}
}
