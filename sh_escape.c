/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:23:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/03 19:21:32 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	charset[] = "\"\'\\";

static inline void	set_escape(char *escape, unsigned int index)
{
	*(escape + index / 8) |= (1 << (index % 8));
}

static void *escape_fonctions(char c)
{

}

char		sh_escape(char *str, char **escaped)
{
	char		(*f)(char *, char *);
	int			i;

	if (!str || (i = ft_strlen(str)) <= 0)
		return (-1);
	escaped = ft_memalloc((i / 8) + 1);
	i = 0;
	while (*(str + i))
	{

	}
	return (0);
}