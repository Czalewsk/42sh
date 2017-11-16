/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:44:32 by bviala            #+#    #+#             */
/*   Updated: 2017/06/29 16:15:41 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			my_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int			solve_c(t_temple *temple, va_list ap)
{
	char	c;
	int		len;
	int		ret;

	ret = 0;
	c = (char)va_arg(ap, int);
	len = ft_strlen(&c);
	if (temple->flag & FLAG_MOINS && temple->flag & FLAG_0)
		temple->flag -= FLAG_0;
	temple->width--;
	ret += (!(temple->flag & FLAG_MOINS)) ?
		(print_blank(temple) + my_putchar(c)) :
		(my_putchar(c) + print_blank(temple));
	return (ret);
}
