/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:20:12 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/03 12:28:11 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define X 0
# define Y 1
# define Z 2
# define C 3
# define KEYS1 (key >= 123 && key <= 126) || key == 8 || key == 9
# define KEYS2 key == 35 || key == 24|| key == 27 || key == 53 || key == 11
# define KEYS3 key == 43 || key == 47 || key == 31 || key == 34

# include "mlx.h"
# include "ft_printf.h"
# include <math.h>
# include <pthread.h>

typedef struct	s_input
{
	int		dim[2];
	int		**coords;
	int		bpp;
	int		sl;
	int		endian;
	float	alt;
	float	zoom;
	int		y_adj;
	int		**p;
	int		x_adj;
	int		isize;
	int		colour;
	int		col_adj;
	int		peaks;
	float	rot;
	int		width;
	int		height;
	int		x;
	int		y;
	int		border;
	char	*data;
	void	*mlx;
	void	*win;
	void	*img;
	int		tw;
	int		th;
}				t_input;

void			fdf(t_input *input);
void			put_pixel_img(t_input *i, int x, int y, int color);
void			print_toscreen(t_input *input);
void			draw_line(int p1[4], int p2[4], t_input *input);
void			build_borders(t_input *i);
void			add_mapkey(t_input *i);

#endif
