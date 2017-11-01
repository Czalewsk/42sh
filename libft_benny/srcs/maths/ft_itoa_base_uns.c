/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:39:34 by bviala            #+#    #+#             */
/*   Updated: 2017/08/16 19:35:52 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base_uns(uintmax_t nbr, int base)
{
	char		*s;
	int			len;
	uintmax_t	nb;

	if (base < 2 || base > 16)
		return (NULL);
	nb = nbr;
	len = 1;
	while ((nbr /= base) != 0)
		len++;
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	*s = '0';
	while (nb != 0)
	{
		s[--len] = HEXA[nb % base];
		nb /= base;
	}
	return (s);
}
