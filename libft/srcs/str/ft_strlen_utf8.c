/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_utf8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:47:16 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/14 18:06:09 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			check_validate_char(char *str, unsigned char msk)
{
	int		nbyte;
	int		i;

	nbyte = 1;
	i = 16;
	while (msk & (i >> (nbyte - 1)) && nbyte < 5)
		++nbyte;
	i = 1;
	if (nbyte > 5)
		return (-1);
	while (++i < nbyte && *(++str))
		if ((*str & 0xc0) != 0x80)
			return (-1);
	if (i != nbyte)
		return (-1);
	return (nbyte - 1);
}

int					ft_strlen_utf8(char *str)
{
	int		len;
	int		nbyte;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		nbyte = 1;
		if (*str < 0 &&
		((nbyte = check_validate_char(str, (unsigned char)*str >> 3)) == -1))
			return (-1);
		len++;
		str += nbyte;
	}
	return (len);
}

int					ft_strnlen_utf8(char *str, int n)
{
	int		len;
	int		nbyte;

	len = 0;
	if (!str)
		return (0);
	while (*str && n > 0)
	{
		nbyte = 1;
		if (*str < 0 &&
		((nbyte = check_validate_char(str, (unsigned char)*str >> 3)) == -1))
			return (-1);
		len++;
		str += nbyte;
		n -= nbyte;
	}
	return (len);
}
