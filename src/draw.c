#include "fdf.h"

void	get_pixels(int *coords, int *pixel, t_input *input)
{
	int		d;
	float	div;
	int		tmp;

	d = input->dim[X] + input->dim[Y] - 2;
	div = (float)coords[Z] / 7;
	div *= (400 / d);
	tmp = (!coords[Z]) ? (int)div : (int)(div * input->alt);
	pixel[X] = 125 + ((550 / d) * coords[X]) + ((550 / d) * ((input->dim[Y] - 1) - coords[Y])) + input->x_adj;
	pixel[Y] = 300 + ((400 / d) * coords[X]) - ((400 / d) * ((input->dim[Y] - 1) - coords[Y])) - tmp - input->height;
}

void	gentle_line(int p1[2], int p2[2], void *mlx, void *win)
{
	int dx;
	int dy;
	int	p;
	int	neg;

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
		mlx_pixel_put(mlx, win, p1[X]++, p1[Y], 0xFFFFFF);
	}	
}

void	steep_line(int p1[2], int p2[2], void *mlx, void *win)
{
	int dx;
	int dy;
	int	p;
	int	k;
	int	neg;
	
	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	k = 0;
	dx = ft_abs(p2[X] - p1[X]);
	dy = ft_abs(p2[Y] - p1[Y]);
	p = 2 *dx - dy;
	while (k++ < dy)
	{
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p1[X]++;
			p = p + 2 * dx - 2 * dy; 
		}
		mlx_pixel_put(mlx, win, p1[X] - 1, p1[Y], 0xFFFFFF);
		p1[Y] += neg;
	}	
}

void	draw_line(int p1[2], int p2[2], void *mlx, void *win)
{
	int p1_copy[2];
	int	p2_copy[2];
	int	i;

	i = 0;
	while (i < 2)
	{
		p1_copy[i] = p1[i];
		p2_copy[i] = p2[i];
		i++;
	}
	if (ft_abs((p2[Y] - p1[Y]) / (p2[X] - p1[X])) >= 1)
		steep_line(p1_copy, p2_copy, mlx, win);
	else
		gentle_line(p1_copy, p2_copy, mlx, win);
}

void	print_toscreen(t_input *input)
{
	int		j;
	int		pixels[input->dim[X] * input->dim[Y]][2];

	j = -1;	
	while (++j < input->dim[X] * input->dim[Y])
		get_pixels(input->coords[j], pixels[j], input);
	while (--j > 0)
	{
		if (j - input->dim[X] >= 0) 
			draw_line(pixels[j], pixels[j - input->dim[X]], input->mlx, input->win);
		if (j % input->dim[X])
			draw_line(pixels[j - 1], pixels[j], input->mlx, input->win);
	}
}
