/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 11:59:57 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/03 20:03:16 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reprint(t_input *input, int key)
{
	int	i;

	i = 0;
	free(input->data);
	free(input->img);
	while (i < input->dim[X] * input->dim[Y])
	{
		if (key == 53)
			free(input->coords[i]);
		free(input->p[i++]);
	}
	if (key == 53)
	{
		free(input->p);
		free(input->coords);
		exit(1);
	}
	mlx_clear_window(input->mlx, input->win);
	print_toscreen(input);
}

void	translation(t_input *i, int key)
{
	int c[4];
	int	j;

	c[0] = i->isize - 10;
	c[1] = 10;
	c[2] = i->isize - 80;
	c[3] = 80;
	j = -1;
	while (++j < i->dim[X] * i->dim[Y])
		if (i->p[j])
		{
			c[0] = (i->p[j][X] < c[0]) ? i->p[j][X] : c[0];
			c[1] = (i->p[j][X] > c[1]) ? i->p[j][X] : c[1];
			c[2] = (i->p[j][Y] < c[2]) ? i->p[j][Y] : c[2];
			c[3] = (i->p[j][Y] > c[3]) ? i->p[j][Y] : c[3];
		}
	if (key == 126 && (c[3] - 20 * i->zoom) > 80)
		i->y_adj -= 20 * i->zoom;
	if (key == 125 && (c[2] + 20 * i->zoom) < i->isize - 80)
		i->y_adj += 20 * i->zoom;
	if (key == 123 && (c[1] - 20 * i->zoom) > 10)
		i->x_adj -= 20 * i->zoom;
	if (key == 124 && (c[0] + 20 * i->zoom) < i->isize - 10)
		i->x_adj += 20 * i->zoom;
}

int		deal_key(int key, t_input *i)
{
	if (key == 126 || key == 125 || key == 123 || key == 124)
		translation(i, key);
	if (key == 34 && i->alt < 5.6)
		i->alt += 0.2;
	if (key == 31 && i->alt > -5.6)
		i->alt -= 0.2;
	if (key == 35)
		i->peaks = (i->peaks) ? 0 : 1;
	if (key == 8)
		i->col_adj += (5 * 1 << 16) + 5;
	if (key == 9)
		i->col_adj -= (5 * 1 << 16) + 5;
	if (key == 11)
		i->col_adj = 0;
	if (key == 24 && i->zoom + 0.3 < 10)
		i->zoom += 0.3;
	if (key == 27 && i->zoom > (float)0.3)
		i->zoom -= 0.3;
	if (key == 43 && i->rot < 2)
		i->rot += 0.2;
	if (key == 47 && i->rot > -2)
		i->rot += -0.2;
	if (KEYS1 || KEYS2 || KEYS3)
		reprint(i, key);
	return (key);
}

void	fdf(t_input *input)
{
	input->p = malloc(sizeof(int *) * input->dim[X] * input->dim[Y]);
	input->alt = 1;
	input->height = 0;
	input->peaks = 0;
	input->y_adj = 0;
	input->col_adj = 0;
	input->zoom = 1;
	input->x_adj = 0;
	input->rot = 1;
	input->mlx = mlx_init();
	input->win = mlx_new_window(input->mlx, input->isize, input->isize, "FDF");
	print_toscreen(input);
	mlx_do_key_autorepeaton(input->mlx);
	mlx_hook(input->win, 2, 0, deal_key, input);
	mlx_loop(input->mlx);
	mlx_loop_hook(input->mlx, deal_key, input);
}
