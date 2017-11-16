/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:48:42 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:48:44 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef HEXA
# define HEXA "0123456789ABCDEF"
#endif

void	ft_putnbr_base(int nb, int base)
{
	int	nbr;
	int	len;
	int	pow;
	int	neg;

	if (base < 2 || base > 16)
		return ;
	nbr = nb;
	neg = (nb < 0) ? 1 : 0;
	len = 0;
	pow = 1;
	if (neg)
		ft_putchar('-');
	while (nbr /= base)
		len++;
	while (len--)
		pow *= base;
	while (pow)
	{
		ft_putchar((nb < 0) ? HEXA[(nb / pow) * -1] : HEXA[nb / pow]);
		nb %= pow;
		pow /= base;
	}
}
