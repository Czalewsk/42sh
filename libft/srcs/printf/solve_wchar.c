/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_wchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 09:21:15 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:18:04 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putwchar(wchar_t c)
{
	if (c <= 0x7F)
		ft_putchar(c);
	else if (c <= 0x7FF)
	{
		ft_putchar((c >> 6) + 0xC0);
		ft_putchar((c & 0x3f) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar((c >> 12) + 0xE0);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3f) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar((c >> 18) + 0xF0);
		ft_putchar(((c >> 12) & 0x3F) + 0x80);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3f) + 0x80);
	}
}

int			len_wchar(wchar_t c, int len)
{
	if (c <= 0x7F)
		len = 1;
	else if (c <= 0x7FF)
		len = 2;
	else if (c <= 0xFFFF)
		len = 3;
	else if (c <= 0x10FFFF)
		len = 4;
	else
		len = 0;
	return (len);
}

int			solve_wchar(t_temple *temple, va_list ap)
{
	wchar_t	c;
	int		len;
	int		ret;

	len = 0;
	ret = 0;
	c = (wchar_t)va_arg(ap, wint_t);
	len = len_wchar(c, len);
	if (temple->flag & FLAG_MOINS && temple->flag & FLAG_0)
		temple->flag -= FLAG_0;
	if (temple->width != 0 && temple->precision == -1 && temple->width <= len)
		temple->width = 0;
	if (temple->width != 0 && temple->precision == -1 && temple->width > len)
		temple->width -= len;
	if (temple->width != 0 && temple->precision != -1)
		temple->width -= len;
	if (temple->precision != -1 && temple->precision >= len)
		temple->precision = len;
	if (!(temple->flag & FLAG_MOINS))
		ret += print_blank(temple);
	ft_putwchar(c);
	if (temple->flag & FLAG_MOINS)
		ret += print_blank(temple);
	return (ret + len);
}
