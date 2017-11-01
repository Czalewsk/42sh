/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:11:50 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:16:40 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_p(t_temple *temple, char *str)
{
	int		ret;

	ret = 2;
	temple->width -= 2;
	if (temple->flag & FLAG_0)
		ft_putstr("0x");
	if (!(temple->flag & FLAG_MOINS))
		ret += print_blank(temple);
	if (!(temple->flag & FLAG_0))
		ft_putstr("0x");
	ret += print_zero(temple) + print_wsign(str, temple);
	if (temple->flag & FLAG_MOINS)
		ret += print_blank(temple);
	ft_strdel(&str);
	return (ret);
}

int			solve_p(t_temple *temple, va_list ap)
{
	int		len;
	char	*str;

	str = conv_unsin(temple, ap, 16);
	len = ft_strlen(str);
	if (temple->precision == 0 && str[0] == '0')
	{
		ft_putstr("0x");
		return (2);
	}
	if (temple->width != 0 && temple->width <= len)
		temple->width = 0;
	if (temple->width != 0 && temple->precision == -1 && temple->width > len)
		temple->width -= len;
	if (temple->width != 0 && temple->precision != -1 && temple->width > len)
		temple->width -= temple->precision;
	if (temple->precision != -1 && temple->precision <= len)
	{
		temple->width -= (len - temple->precision);
		temple->precision = 0;
	}
	if (temple->precision != -1 && temple->precision > len)
		temple->precision -= len;
	return (print_p(temple, str));
}
