/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strxjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 14:11:09 by czalewsk          #+#    #+#             */
/*   Updated: 2017/10/18 10:37:36 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strxjoin(int nb_elemt, ...)
{
	int			i;
	int			len;
	va_list		str;
	char		*joint;

	i = -1;
	len = 0;
	va_start(str, nb_elemt);
	while (++i < nb_elemt)
		len += ft_strlen(va_arg(str, char *));
	va_end(str);
	joint = ft_strnew(len);
	va_start(str, nb_elemt);
	i = -1;
	while (++i < nb_elemt)
		ft_strcat(joint, va_arg(str, char *));
	return (joint);
}
