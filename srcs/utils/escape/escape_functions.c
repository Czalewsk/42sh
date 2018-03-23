/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 21:51:41 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/23 11:19:14 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_escape.h"

extern inline void	set_escape(char *str, unsigned int index, char bit)
{
	*(str + index) |= (1 << bit);
}

void				*sh_esc_squote(char *str, char *to_remove,
		int *index)
{
	if (*str != '\'')
		return (&sh_esc_squote);
	set_remove(to_remove, *index);
	++g_nb_remove;
	return (&escape_fonctions);
}

void				*sh_esc_bslash(char *str, char *to_remove, int *index)
{
	(void)str;
	(void)to_remove;
	(void)index;
	return (&escape_fonctions);
}
