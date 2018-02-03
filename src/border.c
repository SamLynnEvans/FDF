/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 11:39:12 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/03 11:44:15 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	build_borders(t_input *i)
{
	int	x;
	int	y;

	i->border = 1;
	y = 0;
	while (y < i->isize)
	{
		x = 0;
		while (x < i->isize && (y < 70 || y >= i->isize - 70))
			put_pixel_img(i, x++, y, 0xCCFFFF);
		y++;
	}
	i->border = 0;
}

void	add_mapkey(t_input *i)
{
	int x;

	x = (i->isize - 850) / 2;
	mlx_string_put(i->mlx, i->win, 30, 20, 0x000000,
	"- Slynn-ev homebrewed wire frame v1.0");
	mlx_string_put(i->mlx, i->win, x, i->isize - 47, 0x000000, "KEY");
	mlx_string_put(i->mlx, i->win, x + 80, i->isize - 60, 0x000000,
	"+ / - : zoom in / out");
	mlx_string_put(i->mlx, i->win, x + 80, i->isize - 35, 0x000000,
	"i / o : altitude up / down");
	mlx_string_put(i->mlx, i->win, x + 380, i->isize - 60, 0x000000,
	"< / >  : rotate up / down");
	mlx_string_put(i->mlx, i->win, x + 380, i->isize - 35, 0x000000,
	"arrows : move shape");
	mlx_string_put(i->mlx, i->win, x + 680, i->isize - 60, 0x000000,
	"p : colour peaks");
	mlx_string_put(i->mlx, i->win, x + 680, i->isize - 35, 0x000000,
	"c : change colour");
}
