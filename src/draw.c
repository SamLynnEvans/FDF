#include "fdf.h"

void	print_intarr(int *arr, int len)
{
	int i;

	i = 0;
	while (i < len)
		ft_putnbr(arr[i++]);
}
/*
int	*get_pixels(int *coords, t_input *input)
{
	float	div;
	int		tmp;
	int		*pixel;

	pixel = malloc(sizeof(int) * 4);
	div = (float)coords[Z] / 7;
	div *= input->height;
	tmp = (int)(div * input->alt);
	pixel[X] = input->x + (input->width * coords[X]) +
	input->width * ((input->dim[Y] - 1) - coords[Y]) + input->x_adj;
	pixel[Y] = input->y + (input->height * coords[X]) * input->rot -
	(input->height * ((input->dim[Y] - 1) - coords[Y])) * input->rot - tmp - input->y_adj;
	pixel[Z] = coords[Z];
	if (!input->peaks)
		pixel[C] = (coords[C]) ? coords[C] : input->colour;
	else
	pixel[C] = (coords[Z] && input->peaks) ?
	5073779 + ((1 + (1 << 16)) * (coords[Z] * input->alt)) : input->colour;
	return (pixel);
}
*/
void	get_pixels(int *coords, int *pixel, t_input *input)
{
	float	div;
	int		tmp;

	div = (float)coords[Z] / 7;
	div *= input->height;
	tmp = (int)(div * input->alt);
	pixel[X] = input->x + (input->width * coords[X]) +
	input->width * ((input->dim[Y] - 1) - coords[Y]) + input->x_adj;
	pixel[Y] = input->y + (input->height * coords[X]) * input->rot -
	(input->height * ((input->dim[Y] - 1) - coords[Y])) * input->rot - tmp - input->y_adj;
	pixel[Z] = coords[Z];
	if (!input->peaks)
		pixel[C] = (coords[C]) ? coords[C] : input->colour;
	else
	pixel[C] = (coords[Z] && input->peaks) ?
	5073779 + ((1 + (1 << 16)) * (coords[Z] * input->alt)) : input->colour;
}

void	put_pixel_img(t_input *i, int x, int y, int color)
{
	int	pos;
	
	pos = (x * 4) + (y * i->sl);
	i->data[pos++] = color; 
	i->data[pos++] = color >> 8; 
	i->data[pos] = color >> 16;
}

void	gentle_line(int p1[4], int p2[4], t_input *input)
{
	int dx;
	int dy;
	int	p;
	int	neg;
	int	col;

	col = (p1[Z] > p2[Z]) ? p1[C] : p2[C];
	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	dx = ft_abs(p2[X] - p1[X]);
	dy = ft_abs(p2[Y] - p1[Y]);
	p = 2 *dy - dx;
	while (p1[X] < p2[X])
	{
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p1[Y] += neg;
			p = p + 2 * dy - 2 * dx; 
		}
		put_pixel_img(input, p1[X]++, p1[Y], col);
	}	
}


void	steep_line(int p1[4], int p2[4], t_input *input)
{
	int dx;
	int dy;
	int	p;
	int	neg;
	int	col;

	col = (p1[Z] > p2[Z]) ? p1[C] : p2[C];
	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	dx = ft_abs(p2[X] - p1[X]);
	dy = ft_abs(p2[Y] - p1[Y]);
	p = 2 *dx - dy;
	while (p1[X] < p2[X])
	{
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p1[X]++;
			p = p + 2 * dx - 2 * dy; 
		}
		put_pixel_img(input, p1[X] - 1, p1[Y], col);
		p1[Y] += neg;
	}	
}

void	draw_line(int p1[4], int p2[4], t_input *input)
{
	int p1_copy[4];
	int	p2_copy[4];
	int	i;

	i = 0;
	while (i < 4)
	{
		p1_copy[i] = p1[i];
		p2_copy[i] = p2[i];
		i++;
	}
	if ((p2[X] - p1[X] != 0) && ft_abs((p2[Y] - p1[Y]) / (p2[X] - p1[X])) >= 1)
		steep_line(p1_copy, p2_copy, input);
	else
		gentle_line(p1_copy, p2_copy, input);
}
/*
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
		if (j - input->dim[X] >= 0) 
			draw_line(input->pixels[j], input->pixels[j - input->dim[X]], input);
		if (j % input->dim[X])
			draw_line(input->pixels[j - 1], input->pixels[j], input);
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
			if (j - input->dim[X] >= 0) 
			draw_line(input->pixels[j], input->pixels[j - input->dim[X]], i);
		if (j % input->dim[X])
			draw_line(input->pixels[j - 1], input->pixels[j], i);
		j--;
	}
	return (NULL);
}
*/

void	print_toscreen(t_input *i)
{
	int		j;
	int		pixels[i->dim[X] * i->dim[Y]][4];
	int		d;
//	pthread_t fast;

//	pixels = malloc(sizeof(int *) * i->dim[X] * i->dim[Y]);
	i->img = mlx_new_image(i->mlx, i->isize, i->isize);
	i->data = mlx_get_data_addr(i->img, &(i->bpp), &(i->sl), &(i->endian));
	j = -1;
	d = i->dim[X] + i->dim[Y] - 2;
	while (!((i->height = ceil((i->isize * 2) / 5) / d) * i->zoom))
		d--;
	i->height = ceil(((i->isize * 2) / 5) / d) * i->zoom;
	i->width = ceil(((i->isize * 4) / 5) / d) * i->zoom;
	i->x = (i->isize - (i->width * d)) / 2;
	i->y = ((i->isize - (i->height * d)) * 2) / 3;
	while (++j < i->dim[X] * i->dim[Y])
		get_pixels(i->coords[j], pixels[j], i);
//	pthread_create(&fast, NULL, thread_second, i);
//	thread_first(i);
//	pthread_join(fast, NULL);
	while (--j > 0)
	{
		if (j - i->dim[X] >= 0 && pixels[j][X] <= i->isize && pixels[j][Y] <= i->isize && pixels[j - i->dim[X]][X] <= i->isize && pixels[j - i->dim[X]][Y] <= i->isize
		&& pixels[j][X] >=  0 && pixels[j][Y] >= 0 && pixels[j - i->dim[X]][X] >= 0 && pixels[j - i->dim[X]][Y] >= 0)
			draw_line(pixels[j], pixels[j - i->dim[X]], i);
		if (j % i->dim[X] && pixels[j][X] <= i->isize && pixels[j][Y] <= i->isize && pixels[j -1][X] <= i->isize && pixels[j-1][Y] <= i->isize
		&& pixels[j][X] >= 0 && pixels[j][Y] >= 0 && pixels[j -1][X] >= 0 && pixels[j-1][Y] >= 0)
			draw_line(pixels[j - 1], pixels[j], i);
	}
	mlx_put_image_to_window(i->mlx, i->win, i->img, 0, 0);
	free(i->data);
}
