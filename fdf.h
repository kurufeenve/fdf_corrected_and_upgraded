/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 19:11:38 by vordynsk          #+#    #+#             */
/*   Updated: 2018/02/13 19:11:39 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/includes/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>

typedef union		u_color
{
	int				color;
	unsigned char	channel[4];
}					t_color;

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
	t_color			color;
}					t_point;

typedef struct		s_general
{
	int				fd;
	int				i;
	int				j;
	int				n;
	int				m;
	int				len;
	int				rows;
	int				len_buff;
	char			*line;
	char			*line_buff;
	char			**buff;
	t_point			*points;
	void			*init;
	void			*win;
	int				size_x;
	int				size_y;
	int				scale_x;
	int				scale_y;
	int				scale_z;
	void			*img;
	char			*image;
	int				bpp;
	int				val;
	int				ed;
	double			x0;
	double			y0;
	double			x1;
	double			y1;
	double			k;
	double			b;
	double			dx;
	double			dy;
	t_point			center;
	t_color			color;
	t_color			text;
}					t_general;

void				init(t_general *gen);
t_point				init_point(double x, double y, double z, t_color color);
int					count(t_general *gen, char *filename);
void				ft_map(t_general *gen, char *filename);
void				ft_scale(t_general	*gen);
void				turn(t_general *gen, double a, double b, double g);
void				ft_line(t_general *gen);
int					defline(t_general *gen, int i, int l);
int					coefline(t_general	*gen);
void				vertline(t_general *gen, t_color color);
void				coordswap(t_general *gen);
void				plotline(t_general *gen);
void				put_pixel(t_general *gen, int x, int y, t_color color);
int					exit_x(void);
int					key_hook(int key, void *ptr);
void				ft_clearscr(t_general *gen);
void				ft_zoom(t_general *gen, int b);
void				color_change(t_general *gen, int key);
void				ft_screen_stuff(t_general *gen);
void				ft_move(t_general *gen, int key);
void				ft_short_lines(t_general *gen, int	l);
void				ft_center(t_general *gen);
void				ft_winsize(t_general *gen);

#endif
