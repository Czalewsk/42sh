/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:47:43 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/29 16:16:39 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_escape.h"

const char			g_escape_char[] = "|&;<>()$`\\\"\' \t\n*?[#";

static inline int	count_bit(unsigned char *is_escape, int size)
{
	int				i;
	int				res;
	unsigned char	tmp;

	res = 0;
	i = -1;
	while (++i < size)
	{
		tmp = *(is_escape + i);
		res += (((tmp + (tmp >> 4) & 0xF0F0F0F) * 0x1010101) >> 24);
	}
	return (res);
}

char				*escape_it(char *str)
{
	char	*is_escape;
	char	*res;
	char	*new;
	int		i;

	i = -1;
	is_escape = ft_memalloc((ft_strlen(str) / 8) + 1);
	while (*(str + ++i))
		if (ft_strchr(g_escape_char, *(str + i)))
			set_remove(is_escape, i);
	res = ft_strnew(i + count_bit((unsigned char *)is_escape, (i / 8) + 1));
	new = res;
	i = -1;
	while (*(str + ++i))
	{
		if (esc_remove(is_escape, i))
			*new++ = '\\';
		*new++ = *(str + i);
	}
	return (res);
}
