/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 08:29:26 by bviala            #+#    #+#             */
/*   Updated: 2017/08/15 13:55:23 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_blank(t_temple *temple)
{
	int	len;

	len = 0;
	while (temple->width > 0)
	{
		if (temple->flag & FLAG_0)
			ft_putchar('0');
		else
			ft_putchar(' ');
		temple->width--;
		len++;
	}
	return (len);
}

int		print_hexa(t_temple *temple)
{
	if (temple->conv == 'x')
		ft_putstr("0x");
	if (temple->conv == 'X')
		ft_putstr("0X");
	return (2);
}

int		print_zero(t_temple *temple)
{
	int count;

	count = 0;
	while (temple->precision > 0)
	{
		ft_putchar('0');
		temple->precision--;
		count++;
	}
	return (count);
}

int		print_preci(char *str, t_temple *temple)
{
	int i;

	i = 0;
	if (temple->precision != -1 && str[i])
	{
		while (temple->precision > 0)
		{
			ft_putchar(str[i]);
			temple->precision--;
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			i++;
		}
	}
	return (i);
}

int		print_wsign(char *str, t_temple *temple)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (temple->conv == 'X' && (str[i] >= 97 && str[i] < 122))
			str[i] -= 32;
		if (str[i] == '+' || str[i] == '-')
			i++;
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}
