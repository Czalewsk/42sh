/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:39:34 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:07:31 by thugo            ###   ########.fr       */
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
	s = (char*)ft_memalloc(sizeof(char) * (len + 1));
	s[len] = '\0';
	*s = '0';
	while (nb != 0)
	{
		s[--len] = HEXA[nb % base];
		nb /= base;
	}
	return (s);
}
