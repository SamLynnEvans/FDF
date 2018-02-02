#include "fdf.h"

int	get_x(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			count++;
			while (ft_isdigit(str[i]))
				i++;
		}
		if (str[i] == ',')
		{
			i++;
			while (ft_isdigit(str[i]) || HEX_CHAR1 || HEX_PREC )
				i++;
		}
		i++;
	}
	return (count);
}

int	get_map(char **str, int dim[2], int fd)
{
	char	*line;
	int		ret;

	dim[Y] = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		line = ft_strjoin_free(line, " ");
		if (dim[Y] == 0)
		{
			*str = ft_strdup(line);
			dim[X] = get_x(line);
		}
		else
		{
			if (dim[X] != get_x(line))
				return (-1);
			*str = ft_strjoin_free(*str, line);
		}
		free(line);
		dim[Y]++;
	}
	return (ret);
}

int main(int ac, char **av)
{
	char	*map;
	t_input	input;
	int		fd;

	input.p = malloc(sizeof(int *));
	input.p[0] = malloc(sizeof(int));
	input.p[0][0] = 1;
	input.isize = (ac > 2 && ft_isdigit(av[2][0])) ? ft_atoi(av[2]) : 1000;
	input.isize = (input.isize < 850) ? 850 : input.isize;
	input.colour = (ac > 3 && ft_isdigit(av[3][0])) ? ft_atoi(av[3]) : 0xFFFFFF;
	fd = (ac > 1) ? open(av[1], O_RDONLY) : 0;
	if (fd == -1)
		return (0);
	get_map(&map, input.dim, fd);
	if (ac > 2)
		close(fd);
	fdf(map, &input);
}
