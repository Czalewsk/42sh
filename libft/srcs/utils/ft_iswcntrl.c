/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswcntrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:11:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/14 17:06:50 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_iswcntrl(unsigned int c)
{
	if (c < 0x20 || c == 0x7f)
		return (1);
	else if (c > 0x19 && c < 0x7f)
		return (0);
	else if ((c >= 0x1a && c <= 0x1f) || c == 0xad)
		return (1);
	else if (c >= 0x80 && c <= 0x9f)
		return (1);
	else
		return (0);
}
