#include "fdf.h"

void	quit(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->dim[X] * input->dim[Y])
		free(input->coords[i++]);
	free(input->coords);
	exit(1);
}

int	deal_key(int key, t_input *input)
{
	int	i;

	i = 0;
	ft_intdebug(key, "key");
	if (key == 53)
		quit(input);
	if (key == 126)
		input->height += 4;
	if (key == 125)
		input->height -= 4;
	if (key == 123)
		input->x_adj -= 4;
	if (key == 124)
		input->x_adj += 4;
	if (key == 34)
		input->alt += 0.2;
	if (key == 31)
		input->alt -= 0.2;
	if (key == 45 || key == 31 || key == 34 || (key >= 123 && key <= 126))
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

void	fdf(char *str, int dim[2])
{
	t_input input;
	
	input.alt = 1;
	input.height = 0;
	input.x_adj = 0;
	input.dim[X] = dim[X];
	input.dim[Y] = dim[Y];
	input.mlx = mlx_init();
	input.win = mlx_new_window(input.mlx, 800, 800, "FDF");
	input.coords = get_coords(str, dim);
	free(str);
	print_toscreen(&input);
	mlx_key_hook(input.win, deal_key, &input);
	mlx_loop(input.mlx);
}
