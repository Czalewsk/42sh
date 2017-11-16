/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 08:12:09 by bviala            #+#    #+#             */
/*   Updated: 2017/08/15 13:54:58 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_o(t_temple *temple, char *str, int len)
{
	int		ret_val;

	ret_val = 0;
	if (temple->precision != -1 && temple->precision > len)
		temple->precision -= len;
	if (temple->flag & FLAG_DIESE && str[0] != '0')
		temple->width -= 1;
	if (!(temple->flag & FLAG_MOINS))
		ret_val += print_blank(temple);
	if (temple->flag & FLAG_DIESE && temple->precision > 0
			&& temple->width <= 0)
		temple->precision -= 1;
	if (temple->flag & FLAG_DIESE && str[0] != '0')
		temple->precision += (temple->precision == -1) ? 2 : 1;
	ret_val += print_zero(temple) + print_wsign(str, temple);
	if (temple->flag & FLAG_MOINS)
		ret_val += print_blank(temple);
	ft_strdel(&str);
	return (ret_val);
}

int			solve_o(t_temple *temple, va_list ap)
{
	int		len;
	char	*str;

	str = conv_unsin(temple, ap, 8);
	len = ft_strlen(str);
	if ((temple->precision != -1 || temple->flag & FLAG_MOINS)
			&& temple->flag & FLAG_0)
		temple->flag -= FLAG_0;
	if (temple->width != 0 && temple->width <= len)
		temple->width = 0;
	if (temple->width != 0 && temple->precision == -1 && temple->width > len)
		temple->width -= len;
	if (temple->width != 0 && temple->precision != -1 && temple->width > len)
		temple->width -= temple->precision;
	if (temple->precision == 0 && !(temple->flag & FLAG_DIESE) && str[0] == '0')
	{
		temple->width += 1;
		str = ft_strnew(0);
	}
	if (temple->precision != -1 && temple->precision <= len)
	{
		temple->width -= (len - temple->precision);
		temple->precision = 0;
	}
	return (print_o(temple, str, len));
}
