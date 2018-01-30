#include "fdf.h"

int	print_toscreen(t_input *input);

int	deal_key(int key, t_input *input)
{
	int	i;

	i = 0;
	input->key = 0;
	if (key == 53)
		exit(1);
	if (key == 45)
	{
		mlx_clear_window(input->mlx, input->win);
		print_toscreen(input);
	}
	return (key);
}

int	**get_coords(char *str, int dim[2])
{
	int		i;
	int		**coords;
	int		j;

	j = -1;
	i = 0;
	if(!(coords = malloc(sizeof(int *) * (dim[X] * dim[Y] + 1))))
		return (NULL);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			coords[++j] = malloc(sizeof(int) * 3);
			coords[j][X] = j % dim[X];
			coords[j][Y] = j / dim[X];
			coords[j][Z] = ft_atoi(str + i);
			while (ft_isdigit(str[i]))
				i++;
		}
		i++;
	}
	coords[++j] = 0;
	return (coords);
}

void	print_c(int **coords, int dim[2])
{
	int	i;
	int	j;

	j = 0;
	while (j < dim[Y] * dim[X])
	{
		i = 0;
		while (i < 3)
			ft_printf("%d, ", coords[j][i++]);
		ft_printf("\n");
		j++;
	}
}

void	get_pixels(int *coords, int *pixel, int dim[2])
{
	int		d;
	float	div;

	d = dim[X] + dim[Y] - 2;
	div = (float)coords[Z] / 7;
	div *= (400 / d);
	coords[Z] = (int)div;
	pixel[X] = 125 + ((550 / d) * coords[X]) + ((550 / d) * ((dim[Y] - 1) - coords[Y]));
	pixel[Y] = 300 + ((400 / d) * coords[X]) - ((400 / d) * ((dim[Y] - 1) - coords[Y])) - coords[Z];
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

int	print_toscreen(t_input *input)
{
	int		j;
	int		pixels[input->dim[X] * input->dim[Y]][2];

	input->key = 0;
	j = 0;	
	while (j < input->dim[X] * input->dim[Y])
	{
		get_pixels(input->coords[j], pixels[j], input->dim);
		mlx_pixel_put(input->mlx, input->win, pixels[j][X], pixels[j][Y], 0xFFFFFF);
		j++;
	}
	while (--j > 0)
	{
		if (j - input->dim[X] >= 0) 
			draw_line(pixels[j], pixels[j - input->dim[X]], input->mlx, input->win);
		if (j % input->dim[X])
			draw_line(pixels[j - 1], pixels[j], input->mlx, input->win);
	}
	return (1);
}

void	fdf(char *str, int dim[2])
{
	t_input input;
	
	input.dim[X] = dim[X];
	input.dim[Y] = dim[Y];
	input.mlx = mlx_init();
	input.win = mlx_new_window(input.mlx, 800, 800, "FDF");
	input.coords = get_coords(str, dim);
	print_toscreen(&input);
	mlx_key_hook(input.win, deal_key, &input);
	mlx_loop(input.mlx);
	//print_c(coords, x, y);
}

