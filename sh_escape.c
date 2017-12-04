/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:23:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/04 15:02:40 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char		g_charset[] = "\"\'\\";
unsigned int	g_nb_remove = 0;

static inline void	set_escape(char *str, unsigned int index)
{
	*(str + index / 8) |= (1 << (index % 8));
}

void *sh_esc_bslash(char c, char *escaped, char *to_remove, int index)
{
	(void)c;
	(void)to_remove;
	set_escape(escaped, index - g_nb_remove);
	return (&escape_fonctions);
}

static void *escape_fonctions(char c, char *escaped, char *to_remove, int index)
{
	char	*res;
	const void *fcts[3] = {NULL, NULL, &sh_esc_bslash};

	(void)escaped;
	if ((res = ft_strchr(g_charset, c)))
	{
		++g_nb_remove;
		set_escape(to_remove, index - g_nb_remove);
		return ((void *)fcts[(int)(res - g_charset) + 1]);
	}
	else
		return (&escape_fonctions);
}

char		sh_escape(char *str, char **escaped)
{
	void		*(*f)(char , char *, char *, int);
	char		*to_remove;
	int			i;
	char		ret;

	if (!str || !escaped || (i = ft_strlen(str)) <= 0)
		return (-1);
	ret = 0;
	i = -1;
	f = &escape_fonctions;
	*escaped = ft_memalloc((i / 8) + 1);
	to_remove = ft_memalloc((i / 8) + 1);
	while (*(str + ++i))
		if (!(f = f(*(str + i), *escaped, to_remove, i)))
			ret = 1;
	remove_escape(str, to_remove);
	return (ret);
}