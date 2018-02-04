/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:34:02 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/04 21:51:40 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*get_pixels(int *coords, t_input *i)
{
	float	z_scale;
	int		*pixel;

	pixel = malloc(sizeof(int) * 5);
	z_scale = (float)coords[Z] / 6 * i->height * i->alt;
	pixel[X] = i->x + (i->width * coords[X]) +
		i->width * ((i->dim[Y] - 1) - coords[Y]) + i->x_adj;
	pixel[Y] = i->y + (i->height * coords[X]) * i->rot -
	(i->height * ((i->dim[Y] - 1) - coords[Y])) * i->rot - z_scale + i->y_adj;
	pixel[Z] = coords[Z];
	if (!i->peaks)
		pixel[C] = (coords[C]) ? coords[C] : i->colour;
	else
		pixel[C] = (coords[Z] && i->peaks) ?
			5073779 + ((1 + (1 << 16)) * (coords[Z] * i->alt)) : i->colour;
	pixel[C] += i->col_adj;
	pixel[4] = ((pixel[X] + i->width >= 0) && (pixel[X] - i->width < i->isize) &&
	(pixel[Y] + i->height >= 70) &&
	(pixel[Y] - i->height < i->isize - 70))
	? 1 : 0;
	return (pixel);
}

void	*thread_first(void *i)
{
	int		j;
	int		end;
	t_input *f;

	f = (t_input *)i;
	j = f->dim[X] * f->dim[Y];
	end = (f->dim[X] * f->dim[Y]) / 2;
	while (--j > end)
	{
//		if (j - f->dim[X] >= 0 && f->p[j] && f->p[j - f->dim[X]])
		if (j - f->dim[X] >= 0 && (f->p[j][4] || f->p[j - f->dim[X]][4]))
			draw_line(f->p[j], f->p[j - f->dim[X]], f);
//		if (j % f->dim[X] && f->p[j - 1] && f->p[j])
		if (j % f->dim[X] && (f->p[j][4] || f->p[j - 1][4]))
			draw_line(f->p[j - 1], f->p[j], f);
	}
	return (NULL);
}

void	*thread_second(void *i)
{
	int		j;
	t_input	*f;

	f = (t_input *)i;
	j = (f->dim[X] * f->dim[Y]) / 2;
	while (j >= 0)
	{
//		if (j - f->dim[X] >= 0 && f->p[j] && f->p[j - f->dim[X]])
		if (j - f->dim[X] >= 0)
			draw_line(f->p[j], f->p[j - f->dim[X]], i);
//		if (j % f->dim[X] && f->p[j - 1] && f->p[j])
		if (j % f->dim[X])
			draw_line(f->p[j - 1], f->p[j], i);
		j--;
	}
	return (NULL);
}

void	get_dimensions(t_input *i)
{
	int		big_map;
	int		d;
	int		j;

	j = -1;
	d = i->dim[X] + i->dim[Y] - 2;
	big_map = 0;
	while (!((i->height = ceil((i->isize * 2) / 5) / d) * i->zoom))
	{
		big_map = 1;
		d--;
	}
	build_borders(i);
	i->height = ceil((((i->isize * 2) / 5) / d) * i->zoom);
	i->width = ceil((((i->isize * 4) / 5) / d) * i->zoom);
	i->x = (!big_map) ? (i->isize - (i->width * d)) / 2 : 0;
	i->y = (i->isize - (i->height * d)) / 2 + 100;
	while (++j < i->dim[X] * i->dim[Y])
		i->p[j] = get_pixels(i->coords[j], i);
}

void	print_toscreen(t_input *i)
{
	pthread_t fast;

	i->img = mlx_new_image(i->mlx, i->isize, i->isize);
	i->data = mlx_get_data_addr(i->img, &(i->bpp), &(i->sl), &(i->endian));
	get_dimensions(i);
	pthread_create(&fast, NULL, thread_second, i);
	thread_first(i);
	pthread_join(fast, NULL);
	mlx_put_image_to_window(i->mlx, i->win, i->img, 0, 0);
	add_mapkey(i);
}
