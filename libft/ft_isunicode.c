/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isunicode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 20:44:29 by czalewsk          #+#    #+#             */
/*   Updated: 2017/10/28 20:55:24 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isunicode(long int c)
{
	if (c >= 0x1F && c <= 0xFFFF)
		return ((c != 0x7F && !(c >= 0x80 && c <= 0x9F)) ? 1 : 0);
	if (c >= 0x10000 && c <= 0x1FFFF)
		return (1);
	if (c >= 0x20000 && c <= 0x2FFFF)
		return (1);
	if (c >= 0x30000 && c <= 0xDFFFF)
		return (1);
	return (0);
}