/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:40:03 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/05 12:00:22 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		ft_is_escape(char *esc, char *str)
{
	char		is_escape;

	is_escape = 0;
	while (str && str < esc)
	{
		if (*str == '\\')
			str += *(str + 1) ? 2 : 1;
		if (*str == '\'' || *str == '\"')
		{
			if (!is_escape)
				is_escape = *str;
			else if (is_escape == *str)
				is_escape = 0;
		}
		str += (*str && str != esc) ? 1 : 0;
	}
	is_escape = is_escape ? 1 : 0;
	return (esc == str ? is_escape : -1);
}
