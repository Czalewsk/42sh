/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 21:51:41 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/06 17:06:53 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_escape.h"

extern inline void	set_escape(char *str, unsigned int index, char bit)
{
	*(str + index) |= (1 << bit);
}

void				*sh_esc_squote(char *str, char *escaped, char *to_remove,
		int index)
{
	if (*str != '\'')
	{
		set_escape(escaped, index - g_nb_remove, 0);
		return (&sh_esc_squote);
	}
	set_remove(to_remove, index);
	++g_nb_remove;
	return (&escape_fonctions);
}

void				*sh_esc_bslash(char *str, char *escaped, char *to_remove,
		int index)
{
	(void)str;
	(void)to_remove;
	set_remove(escaped, index - g_nb_remove);
	return (&escape_fonctions);
}
