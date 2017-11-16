/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 06:55:33 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:14:13 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*conv_sin(t_temple *temple, va_list ap)
{
	if (temple->mod == MOD_H)
		return (ft_itoa((short)va_arg(ap, int)));
	else if (temple->mod == MOD_HH)
		return (ft_itoa((signed char)va_arg(ap, int)));
	else if (temple->mod == MOD_L)
		return (ft_itoa(va_arg(ap, long)));
	else if (temple->mod == MOD_LL)
		return (ft_itoa(va_arg(ap, long long)));
	else if (temple->mod == MOD_J)
		return (ft_itoa(va_arg(ap, intmax_t)));
	else if (temple->mod == MOD_Z)
		return (ft_itoa(va_arg(ap, ssize_t)));
	else
		return (ft_itoa(va_arg(ap, int)));
}

char	*conv_unsin(t_temple *temple, va_list ap, int base)
{
	if (temple->mod == MOD_H)
		return (ft_itoa_base_uns(((unsigned short)
						va_arg(ap, unsigned int)), base));
	else if (temple->mod == MOD_HH)
		return (ft_itoa_base_uns(((unsigned char)
						va_arg(ap, unsigned int)), base));
	else if (temple->mod == MOD_L)
		return (ft_itoa_base_uns((va_arg(ap, unsigned long)), base));
	else if (temple->mod == MOD_LL)
		return (ft_itoa_base_uns((va_arg(ap, unsigned long long)), base));
	else if (temple->mod == MOD_J)
		return (ft_itoa_base_uns((va_arg(ap, uintmax_t)), base));
	else if (temple->mod == MOD_Z)
		return (ft_itoa_base_uns((va_arg(ap, size_t)), base));
	else
		return (ft_itoa_base_uns((va_arg(ap, unsigned int)), base));
}
