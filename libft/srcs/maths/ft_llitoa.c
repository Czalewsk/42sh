/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 14:32:59 by bviala            #+#    #+#             */
/*   Updated: 2017/08/16 19:34:10 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_llitoa(long long int nbr)
{
	char			*s;
	int				len;
	int				neg;
	long long int	n;

	n = nbr;
	neg = (nbr < 0) ? 1 : 0;
	len = neg;
	while (++len && n)
		n /= 10;
	if (!(s = (char*)malloc(sizeof(char) * (len))))
		return (NULL);
	s[--len] = '\0';
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

char		*ft_ullitoa(unsigned long long int nbr)
{
	char					*s;
	int						len;
	unsigned long long int	n;

	n = nbr;
	len = 0;
	while (++len && n)
		n /= 10;
	if (!(s = (char*)malloc(sizeof(char) * (len))))
		return (NULL);
	s[--len] = '\0';
	*s = '0';
	while (nbr != 0)
	{
		s[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (s);
}
