/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 13:23:44 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/01 14:00:29 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char g_hex[16] = "0123456789abcdef";

int	get_val(char c)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (c == g_hex[i] || c + 32 == g_hex[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, int base)
{
	int	p;
	int	i;
	int	val;

	i = 0;
	p = 0;
	if (str[i] == '0')
		i++;
	if (str[i] == 'x' || str[i] == 'X')
		i++;
	while (ft_isdigit(str[i]) || HEX_CHAR1 || HEX_PREC)
	{
		if ((val = get_val(str[i])) == -1)
			return (0);
		p = base * p + val % base;
		i++;
	}
	return (p);
}
