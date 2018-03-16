/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:18:16 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:07:02 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(ssize_t nb)
{
	int		len;

	len = 0;
	if (!nb)
		return (1);
	while (nb != 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char		*ft_itoa(ssize_t nbr)
{
	char	*s;
	int		len;
	int		neg;

	neg = (nbr < 0) ? 1 : 0;
	len = ft_count(nbr) + neg;
	s = (char*)ft_memalloc(sizeof(char) * (len + 1));
	s[len] = '\0';
	*s = '0';
	while (nbr != 0)
	{
		s[--len] = (!neg) ? (nbr % 10 + '0') : ((nbr % 10) * -1 + '0');
		nbr /= 10;
	}
	if (neg)
		s[--len] = '-';
	return (s);
}

void		ft_itoa_nm(ssize_t nbr, char *nb)
{
	int		len;
	int		neg;

	neg = (nbr < 0) ? 1 : 0;
	len = ft_count_len(nbr) + neg;
	nb[len] = '\0';
	*nb = '0';
	while (nbr != 0)
	{
		nb[--len] = (!neg) ? (nbr % 10 + '0') : ((nbr % 10) * -1 + '0');
		nbr /= 10;
	}
	if (neg)
		nb[--len] = '-';
}
