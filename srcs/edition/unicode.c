/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:25:42 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/21 13:16:17 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		sh_curs_unicode(char *str, int index, int end)
{
	int				start_char;
	int				i;
	unsigned char	test;
	int				char_visu;

	DEBUG("index = %d(end=%d)(len=%d)\n~%s~\n", index, end, ft_strlen(str), str)
	start_char = 0;
	i = 0;
	char_visu = 0;
	while (((char_visu <= index) || (end && start_char != i - 1)) && (test = *(str + i)))
	{
		if ((test & 0xC0) != 0x80 || ((test & 0xE0) == 0xC0))
		{
			DEBUG("\t\tWHILE=%s|\n", str + i)
			start_char = i;
			char_visu++;
		}
		DEBUG("visu=%d | test=%#X\n", start_char, test)
		i++;
	}
	if (!test)
		start_char = i;
	DEBUG("Index unicode =%d\n", start_char);
	return (start_char);
}