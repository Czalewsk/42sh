/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:23:05 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/29 14:05:38 by czalewsk         ###   ########.fr       */
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
	while (*str)
	{
		if (esc_remove(to_remove, i))
		{
			*str = *(str + 1 + j);
			j++;
			i++;
			continue ;
		}
		(*str = *(str + j));
		str++;
		i++;
	}
}

void				*escape_fonctions(char *str, char *escaped, char *to_remove,
		int index)
{
	char		*res;
	const void	*fcts[3] = {&sh_esc_dquote, &sh_esc_squote, &sh_esc_bslash};

	(void)escaped;
	if ((res = ft_strchr(g_charset, *str)))
	{
		set_remove(to_remove, index);
		++g_nb_remove;
		return ((void *)fcts[(int)(res - g_charset)]);
	}
	else
		return (&escape_fonctions);
}

char				sh_escape(char *str, char **escaped)
{
	void		*(*f)(char *, char *, char *, int);
	char		*to_remove;
	int			i;

	if (!str || !escaped || (i = ft_strlen(str)) <= 0)
		return (-1);
	f = &escape_fonctions;
	*escaped = ft_memalloc((i + 1));
	to_remove = ft_memalloc((i / 8) + 1);
	i = -1;
	while (*(str + ++i))
		f = f(str + i, *escaped, to_remove, i);
	remove_escape(str, to_remove);
	ft_strdel(&to_remove);
	return (f != &escape_fonctions ? 1 : 0);
}

/*
**int		main(void)
**{
**	char str[] = "\"l\\`ol\"";
**	char *l = NULL;
**	char ret;
**
**	ft_printf("Avant=%s|\n", str);
**	ret = sh_escape(str, &l);
**	ft_printf("Retour(%d) Escape=%hhX\nApres=%s|\n", ret, *l, str);
**	ft_printf("\n~%i~\n", SH_IS_END_DQ(l, 2));
**	while (*l)
**		ft_printf("%i", *l++);
**}
*/
