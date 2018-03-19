/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:31:50 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/19 15:35:48 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_xfree(int nb, ...)
{
	va_list		ap;
	void		*to_free;

	va_start(ap, nb);
	while (nb-- > 0)
	{
		to_free = va_arg(ap, void *);
		free(to_free);
	}
	va_end(ap);
}
