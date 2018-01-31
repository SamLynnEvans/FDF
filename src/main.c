#include "fdf.h"

int	get_x(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			count++;
			while (ft_isdigit(line[i]))
				i++;
		}
		i++;
	}
	return (count);
}

int main(int ac, char **av)
{
	char	*coords;
	char	*line;
	int		dim[2];
	int		fd;

	dim[Y] = 0;
	fd = (ac == 2) ? open(av[1], O_RDONLY) : 0;
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoin_free(line, " ");
		if (dim[Y] == 0)
		{
			coords = ft_strdup(line);
			dim[X] = get_x(line);
		}
		else
			coords = ft_strjoin_free(coords, line);
		free(line);
		dim[Y]++;
	}
	if (ac == 2)
		close(fd);
	fdf(coords, dim);
}
