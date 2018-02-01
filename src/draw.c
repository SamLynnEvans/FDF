#include "fdf.h"

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

void	gentle_line(int p1[4], int p2[4], void *mlx, void *win)
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
		mlx_pixel_put(mlx, win, p1[X]++, p1[Y], col);
	}	
}

void	steep_line(int p1[4], int p2[4], void *mlx, void *win)
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
		mlx_pixel_put(mlx, win, p1[X] - 1, p1[Y], col);
		p1[Y] += neg;
	}	
}

void	draw_line(int p1[4], int p2[4], void *mlx, void *win)
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
		steep_line(p1_copy, p2_copy, mlx, win);
	else
		gentle_line(p1_copy, p2_copy, mlx, win);
}
/*
void	*thread_first(int **pixels, t_inut *input, int j)
{
	while (--j > 0)
	{
		if (j - input->dim[X] >= 0) 
			draw_line(pixels[j], pixels[j - input->dim[X]], input->mlx, input->win);
		if (j % input->dim[X])
			draw_line(pixels[j - 1], pixels[j], input->mlx, input->win);
	}
}*/

void	print_toscreen(t_input *input)
{
	int		j;
	int		pixels[input->dim[X] * input->dim[Y]][4];
	int		d;

	j = -1;
	d = input->dim[X] + input->dim[Y] - 2;
	while (!((input->height = ceil((input->isize * 2) / 5) / d) * input->zoom))
		d--;
	input->height = ceil(((input->isize * 2) / 5) / d) * input->zoom;
	input->width = ceil(((input->isize * 4) / 5) / d) * input->zoom;
	input->x = (input->isize - (input->width * d)) / 2;
	input->y = ((input->isize - (input->height * d)) * 2) / 3;
	while (++j < input->dim[X] * input->dim[Y])
		get_pixels(input->coords[j], pixels[j], input);
//	thread_first(pixels, input, j);
//	thread_second(pixels, input, j/2);
	while (--j > 0)
	{
		if (j - input->dim[X] >= 0) 
			draw_line(pixels[j], pixels[j - input->dim[X]], input->mlx, input->win);
		if (j % input->dim[X])
			draw_line(pixels[j - 1], pixels[j], input->mlx, input->win);
	}
}
