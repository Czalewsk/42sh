/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:25:42 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/21 20:57:58 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/*
** Retourne l'index du char visuel 
*/


int		sh_curs_unicode(char *str, int index, int end)
{
	int				start_char;
	int				i;
	unsigned char	test;
	int				char_visu;

	start_char = 0;
	i = 0;
	char_visu = 0;
	test = 0;
	while (((char_visu <= index) 
				|| (end && start_char != i - 1)) && (test = *(str + i)))
	{
		if ((test & 0xC0) != 0x80 || ((test & 0xE0) == 0xC0))
		{
			start_char = i;
			char_visu++;
		}
		i++;
	}
	if (!test)
		start_char = i;
	return (start_char);
}