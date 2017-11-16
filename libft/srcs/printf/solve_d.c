/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:51:18 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:15:55 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_d(t_temple *temple, char *str, int len)
{
	int	ret;

	ret = 0;
	if (temple->precision != -1 && temple->precision > len)
		temple->precision -= len;
	if (temple->flag & FLAG_PLUS || str[0] == '-' || temple->flag & FLAG_ESPACE)
		temple->width--;
	if (temple->flag & FLAG_ESPACE)
		ret += write(1, " ", 1);
	if (str[0] == '-' && temple->flag & FLAG_0)
		ft_putchar('-');
	if (temple->flag & FLAG_PLUS && str[0] != '-' && temple->flag & FLAG_0)
		ret += write(1, "+", 1);
	if (!(temple->flag & FLAG_MOINS))
		ret += print_blank(temple);
	if (str[0] == '-' && !(temple->flag & FLAG_0))
		ft_putchar('-');
	if (temple->flag & FLAG_PLUS && str[0] != '-' && !(temple->flag & FLAG_0))
		ret += write(1, "+", 1);
	ret += (temple->precision == 0 && str[0] == '0') ? 0 :
		print_zero(temple) + print_wsign(str, temple);
	if (temple->flag & FLAG_MOINS)
		ret += print_blank(temple);
	ft_strdel(&str);
	return (ret);
}

int			solve_d(t_temple *temple, va_list ap)
{
	int		len;
	char	*str;

	str = conv_sin(temple, ap);
	len = str[0] != '-' ? ft_strlen(str) : ft_strlen(str) - 1;
	if ((temple->precision != -1 || temple->flag & FLAG_MOINS)
			&& temple->flag & FLAG_0)
		temple->flag -= FLAG_0;
	if ((str[0] == '-' || temple->flag & FLAG_PLUS || temple->width > len) &&
			temple->flag & FLAG_ESPACE && !(temple->flag & FLAG_0))
		temple->flag -= FLAG_ESPACE;
	if (temple->width != 0 && temple->width <= len)
		temple->width = 0;
	if (temple->width != 0 && temple->precision == -1 && temple->width > len)
		temple->width -= len;
	if (temple->width != 0 && temple->precision != -1 && temple->width > len)
		temple->width -= temple->precision;
	if (temple->precision == 0 && str[0] == '0')
		temple->width += 1;
	if (temple->precision != -1 && temple->precision <= len)
	{
		temple->width -= (len - temple->precision);
		temple->precision = 0;
	}
	return (print_d(temple, str, len));
}
