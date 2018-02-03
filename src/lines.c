/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:32:14 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/03 11:46:19 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_img(t_input *i, int x, int y, int color)
{
	int	pos;

	if (!(x >= 0 && x < i->isize && y >= 70 && y < i->isize - 70) && !i->border)
		return ;
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
	p = 2 * dy - dx;
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
	p = 2 * dx - dy;
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
