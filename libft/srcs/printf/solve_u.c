/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:28:40 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:17:30 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_u(t_temple *temple, char *str, int len)
{
	int	ret;

	ret = 0;
	if (temple->precision != -1 && temple->precision > len)
		temple->precision -= len;
	if (!(temple->flag & FLAG_MOINS))
		ret += print_blank(temple);
	ret += print_zero(temple) + print_wsign(str, temple);
	if (temple->flag & FLAG_MOINS)
		ret += print_blank(temple);
	ft_strdel(&str);
	return (ret);
}

int			solve_u(t_temple *temple, va_list ap)
{
	int		len;
	char	*str;

	str = conv_unsin(temple, ap, 10);
	len = ft_strlen(str);
	if ((temple->precision > 0 || temple->flag & FLAG_MOINS)
			&& temple->flag & FLAG_0)
		temple->flag -= FLAG_0;
	if (temple->width != 0 && temple->width <= len)
		temple->width = 0;
	if (temple->width != 0 && temple->precision == -1 && temple->width > len)
		temple->width -= len;
	if (temple->width != 0 && temple->precision != -1 && temple->width > len)
		temple->width -= temple->precision;
	if (temple->precision == 0 && str[0] == '0')
	{
		temple->width += 1;
		str = ft_strnew(0);
	}
	if (temple->precision != -1 && temple->precision <= len)
	{
		temple->width -= (len - temple->precision);
		temple->precision = 0;
	}
	return (print_u(temple, str, len));
}
