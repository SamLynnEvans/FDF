/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 11:59:43 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/03 11:59:45 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_x(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			count++;
			while (ft_isdigit(*str))
				str++;
		}
		if (*str == ',')
		{
			str++;
			while (ft_isdigit(*str) || HEX_CHAR1 || HEX_PREC)
				str++;
		}
		str++;
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

int	get_coords(char *str, t_input *f)
{
	int		j;

	j = -1;
	if (!(f->coords = malloc(sizeof(int *) * (f->dim[X] * f->dim[Y]))))
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			if (!(f->coords[++j] = malloc(sizeof(int) * 4)))
				return (0);
			f->coords[j][X] = j % f->dim[X];
			f->coords[j][Y] = j / f->dim[X];
			f->coords[j][Z] = ft_atoi(str);
			f->coords[j][C] = 0;
			while (ft_isdigit(*str))
				str++;
		}
		if (*str == ',')
			f->coords[j][C] = ft_atoi_base(++str, 16);
		while (ft_isdigit(*str) || HEX_CHAR1 || HEX_PREC)
			str++;
		str++;
	}
	return (1);
}

int	main(int ac, char **av)
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
	if (!(get_coords(map, &input)))
		return (0);
	free(map);
	fdf(&input);
	return (1);
}
