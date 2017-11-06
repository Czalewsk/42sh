/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:38:36 by bviala            #+#    #+#             */
/*   Updated: 2017/08/15 13:46:03 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			print_percent(char *str, t_temple *temple)
{
	int		ret;

	ret = 0;
	if (temple->flag & FLAG_MOINS && temple->flag & FLAG_0)
		temple->flag -= FLAG_0;
	temple->precision = -1;
	temple->width--;
	if (!(temple->flag & FLAG_MOINS))
		ret += print_blank(temple);
	ret += write(1, str, 1);
	if (temple->flag & FLAG_MOINS)
		ret += print_blank(temple);
	return (ret);
}

int			resolver(char **format, va_list ap)
{
	int			i;
	t_temple	temple;

	i = 0;
	parsing(format, &temple);
	if (ft_isaconv(**format))
		temple.conv = **format;
	else
		return (print_percent(*format, &temple));
	i += check_dou(&temple, ap);
	i += check_x(&temple, ap);
	i += check_sc(&temple, ap, *format);
	return (i);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list ap;
	int		ret;

	ret = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				return (ret);
			ret += resolver((char **)&format, ap);
		}
		else
		{
			ret++;
			ft_putchar(*format);
		}
		format++;
	}
	va_end(ap);
	return (ret);
}
