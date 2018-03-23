/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:23:05 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/23 11:19:20 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_escape.h"
#include "utils.h"

const char		g_charset[] = "\"\'\\";
unsigned int	g_nb_remove = 0;

extern inline void	set_remove(char *str, unsigned int index)
{
	*(str + index / 8) |= (1 << (index % 8));
}

extern inline char	esc_remove(char *str, unsigned int index)
{
	return (*(str + index / 8) & (1 << (index % 8)));
}

static void			remove_escape(char *str, char *to_remove)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(str + j))
	{
		if (esc_remove(to_remove, i))
		{
			*str = *(str + 1 + j);
			j++;
			i++;
			continue ;
		}
		*str = *(str + j);
		str++;
		i++;
	}
	*str = '\0';
}

void				*escape_fonctions(char *str, char *to_remove,
		int *i)
{
	char		*res;
	int			index;
	const void	*fcts[3] = {&sh_esc_dquote, &sh_esc_squote, &sh_esc_bslash};

	index = *i;
	if ((res = ft_strchr(g_charset, *str)))
	{
		set_remove(to_remove, index);
		++g_nb_remove;
		return ((void *)fcts[(int)(res - g_charset)]);
	}
	else
		return (&escape_fonctions);
}

void				sh_escape(char *str)
{
	void		*(*f)(char *, char *, int *);
	char		*to_remove;
	int			i;

	if (!str || (i = ft_strlen(str)) <= 0)
		return ;
	f = &escape_fonctions;
	to_remove = ft_memalloc((i / 8) + 1);
	i = -1;
	while (*(str + ++i))
		f = f(str + i, to_remove, &i);
	remove_escape(str, to_remove);
	ft_strdel(&to_remove);
}

/*
**int		main(void)
**{
**	char str[] = "\\\"w\\ewef\\";
**
**	ft_printf("Avant=%s|\n", str);
**	sh_escape(str);
**	ft_printf("Apres=%s|\n", str);
**}
*/
