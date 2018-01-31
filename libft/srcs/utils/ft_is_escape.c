/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_escape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:58:59 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/30 14:05:05 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		ft_is_escape(char *esc, char *str)
{
	char		is_escape;
	char		backslash;

	backslash = 0;
	is_escape = 0;
	if (!str || !esc || esc <= str)
		return (esc == str ? 0 : -1);
	str--;
	while (++str < esc)
	{
		if (backslash)
			backslash = 0;
		else if (is_escape != '\'' && *str == '\\')
			backslash = 1;
		else if (*str == '"' || *str == '\'')
		{
			if (!is_escape)
				is_escape = *str;
			else if (is_escape == *str)
				is_escape = 0;
		}
	}
	return (backslash ? '\\' : is_escape);
}
