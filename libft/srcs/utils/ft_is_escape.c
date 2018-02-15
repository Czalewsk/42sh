/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_escape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:58:59 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/15 05:32:11 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		ft_is_escape(char *esc, char *str)
{
	char		is_escape;
	char		backslash;
	char		change;

	if (!str-- || !esc)
		return (-1);
	change = !(*(&backslash) &= 0) && !(*(&is_escape) &= 0) ? 0 : 0;
	while (++str <= esc)
	{
		if (change && (!(is_escape = (is_escape ? 0 : *(str - 1))) || 1))
			change = 0;
		if (backslash && (is_escape = '\\')
				&& !(change = 0))
			backslash = 0;
		else if (is_escape == '\\')
			is_escape = 0;
		else if (is_escape != '\'' && *str == '\\')
			backslash = 1;
		else if ((!is_escape || *str == is_escape) && (*str == '"' ||
				*str == '\''))
			change = 1;
	}
	return ((is_escape && change) ? 0 : is_escape);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char *str = strdup("\"$arg\"$arg");
	char esc = ft_is_escape(str + 7, str);

	printf("Is Escape: %i [%c]\n", (int)esc, esc);
	return (0);
}
*/
