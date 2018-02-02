/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:34:02 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/02 22:17:00 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*get_pixels(int *coords, t_input *i)
{
	float	z_scale;
	int		*pixel;

	pixel = malloc(sizeof(int) * 4);
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
	return ((pixel[X] + i->width >= 0) && (pixel[X] - i->width < i->isize) && 
	(pixel[Y] + i->height >= 70) && (pixel[Y] - i->height < i->isize - 70)) ?
	pixel : NULL;
}

void	*thread_first(void *i)
{
	int	j;
	int	end;
	t_input *input;

	input = (t_input *)i;
	j = input->dim[X] * input->dim[Y];
	end = (input->dim[X] * input->dim[Y]) / 2;
	while (--j > end)
	{
		if (j - input->dim[X] >= 0 && input->p[j] && input->p[j - input->dim[X]]) 
			draw_line(input->p[j], input->p[j - input->dim[X]], input);
		if (j % input->dim[X] && input->p[j -1] && input->p[j])
			draw_line(input->p[j - 1], input->p[j], input);
	}
	return (NULL);
}

void	*thread_second(void *i)
{
	int	j;
	t_input *input;

	input = (t_input *)i;
	j = (input->dim[X] * input->dim[Y]) / 2;
	while (j >= 0)
	{
		if (j - input->dim[X] >= 0 && input->p[j] && input->p[j - input->dim[X]]) 
			draw_line(input->p[j], input->p[j - input->dim[X]], i);
		if (j % input->dim[X] && input->p[j -1] && input->p[j])
			draw_line(input->p[j - 1], input->p[j], i);
		j--;
	}
	return (NULL);
}

void	build_borders(t_input *i)
{
	int	x;
	int	y;

	i->border = 1;
	y = 0;
	while (y < i->isize)
	{
		x = 0;
		while (x < i->isize && (y < 70 || y >= i->isize - 70))
			put_pixel_img(i, x++, y, 0xCCFFFF);
		y++;	
	}
	/*y = i->isize - 70;
	while (y < i->isize)
	{
		x = 0;
		while (x < i->isize)
			put_pixel_img(i, x++, y, 0xCCFFFF);
		y++;	
	}*/
	i->border = 0;
}

void	print_toscreen(t_input *i)
{
	int		j;
	int		d;
	int		big_map;
	pthread_t fast;

	big_map = 0;
	i->img = mlx_new_image(i->mlx, i->isize, i->isize);
	i->data = mlx_get_data_addr(i->img, &(i->bpp), &(i->sl), &(i->endian));
	j = -1;
	d = i->dim[X] + i->dim[Y] - 2;
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
	pthread_create(&fast, NULL, thread_second, i);
	thread_first(i);
	pthread_join(fast, NULL);
	mlx_put_image_to_window(i->mlx, i->win, i->img, 0, 0);
}
