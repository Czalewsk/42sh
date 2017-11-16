/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_wstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:51:14 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:17:58 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putnwstr(const wchar_t *str, int len)
{
	int i;

	i = 0;
	while (*str && i < len)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		if (i <= len)
			ft_putwchar(*str);
		str++;
	}
	return (i);
}

int			ft_wstrlen_precision(wchar_t *str, int precision, int i)
{
	if (*str == '\0' || precision == 0)
		return (i);
	else if (*str <= 0x7F)
		return (ft_wstrlen_precision(str + 1, precision - 1, i + 1));
	else if (*str <= 0x7FF && precision >= 2)
		return (ft_wstrlen_precision(str + 1, precision - 2, i + 2));
	else if (*str <= 0xFFFF && precision >= 3)
		return (ft_wstrlen_precision(str + 1, precision - 3, i + 3));
	else if (*str <= 0x10FFFF && precision >= 4)
		return (ft_wstrlen_precision(str + 1, precision - 4, i + 4));
	else
		return (i);
}

int			ft_wstrlen(wchar_t *str)
{
	int		i;

	i = 0;
	while (str && *str)
	{
		if (*str <= 0x7F)
			i += 1;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		str++;
	}
	return (i);
}

static int	print_flag_wstr(t_temple *temple, wchar_t *str, int len)
{
	int		ret;

	ret = 0;
	if (!(temple->flag & FLAG_MOINS))
		ret += print_blank(temple);
	ret += ft_putnwstr(str, len);
	if (temple->flag & FLAG_MOINS)
		ret += print_blank(temple);
	return (ret);
}

int			solve_wstring(t_temple *temple, va_list ap)
{
	int		len;
	int		ret;
	wchar_t	*str;

	ret = 0;
	str = va_arg(ap, wchar_t*);
	if (temple->flag & FLAG_MOINS && temple->flag & FLAG_0)
		temple->flag -= FLAG_0;
	if (str == NULL)
		str = L"(null)";
	len = (temple->precision != -1) ?
		ft_wstrlen_precision(str, temple->precision, 0) : ft_wstrlen(str);
	if (temple->width != 0 && temple->precision == -1 && temple->width <= len)
		temple->width = 0;
	if (temple->width != 0 && temple->precision == -1 && temple->width > len)
		temple->width -= len;
	if (temple->width != 0 && temple->precision != -1)
		temple->width -= len;
	if (temple->precision != -1 && temple->precision >= len)
		temple->precision = len;
	return (print_flag_wstr(temple, str, len));
}
