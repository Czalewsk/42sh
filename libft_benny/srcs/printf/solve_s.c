/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:19:49 by bviala            #+#    #+#             */
/*   Updated: 2017/08/15 13:55:48 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			solve_s(t_temple *temple, va_list ap)
{
	int		len;
	char	*str;
	int		ret;

	ret = 0;
	str = va_arg(ap, char*);
	if (temple->flag & FLAG_MOINS && temple->flag & FLAG_0)
		temple->flag -= FLAG_0;
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (temple->precision != -1 && temple->precision >= len)
		temple->precision = len;
	if (temple->width != 0 && temple->precision == -1 && temple->width <= len)
		temple->width = 0;
	if (temple->width != 0 && temple->precision == -1 && temple->width > len)
		temple->width -= len;
	if (temple->width != 0 && temple->precision != -1 && *str)
		temple->width -= temple->precision;
	ret += (!(temple->flag & FLAG_MOINS)) ?
			print_blank(temple) + print_preci(str, temple) :
			print_preci(str, temple) + print_blank(temple);
	return (ret);
}
