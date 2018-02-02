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
	if (key == 53)
		quit(input);
	if (key == 126)
		input->y_adj += 10;
	if (key == 125)
		input->y_adj -= 10;
	if (key == 123)
		input->x_adj -= 10;
	if (key == 124)
		input->x_adj += 10;
	if (key == 34 && input->alt < 5.6)
		input->alt += 0.2;
	if (key == 31)
		input->alt -= 0.2;
	if (key == 35)
		input->peaks = (input->peaks) ? 0 : 1;
	if (key == 8)
		input->colour += (5 * 1 << 16) + 5;
	if (key == 24)
		input->zoom += 0.1;
	if (key == 27 && (input->zoom - 0.1 > 0))
		input->zoom -= 0.1;
	if (key == 43 || key == 47)
		input->rot += (key == 43) ? 0.2 : -0.2;
	if (key == 43 || key == 47 || key == 31 || key == 34 || (key >= 123 && key <= 126) || key == 8 || key == 35 || key == 24|| key == 27)
	{
		mlx_clear_window(input->mlx, input->win);
		print_toscreen(input);
	}
	return (key);
}

int	**get_coords(char *str, t_input *input)
{
	int		i;
	int		**coords;
	int		j;

	j = -1;
	i = -1;
	if(!(coords = malloc(sizeof(int *) * (input->dim[X] * input->dim[Y]))))
		return (NULL);
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
		{
			coords[++j] = malloc(sizeof(int) * 4);
			coords[j][X] = j % input->dim[X];
			coords[j][Y] = j / input->dim[X];
			coords[j][Z] = ft_atoi(str + i);
			coords[j][C] = 0;
			while (ft_isdigit(str[i]))
				i++;
		}
		if (str[i] == ',')
			coords[j][C] = ft_atoi_base(str + ++i, 16);
		while (ft_isdigit(str[i]) || HEX_CHAR1 || HEX_PREC)
			i++;
	}
	return (coords);
}

void	fdf(char *str, t_input *input)
{
	input->alt = 1;
	input->height = 0;
	input->peaks = 0;
	input->zoom = 1;
	input->x_adj = 0;
	input->rot = 1;
	input->mlx = mlx_init();
	input->win = mlx_new_window(input->mlx, input->isize, input->isize, "FDF");
	input->coords = get_coords(str, input);
	free(str);
	print_toscreen(input);
	mlx_key_hook(input->win, deal_key, input);
	mlx_loop(input->mlx);
}
