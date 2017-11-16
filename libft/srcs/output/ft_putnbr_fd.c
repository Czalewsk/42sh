/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:48:59 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:49:02 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_fd(int n, int fd)
{
	long int	stock;

	stock = n;
	if (stock < 0)
	{
		ft_putchar_fd('-', fd);
		stock = -stock;
	}
	if (stock < 10)
		ft_putchar_fd(stock + '0', fd);
	if (stock >= 10)
	{
		ft_putnbr_fd(stock / 10, fd);
		ft_putnbr_fd(stock % 10, fd);
	}
}
