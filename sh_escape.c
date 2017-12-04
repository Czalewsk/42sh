/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:23:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/04 21:23:33 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void *escape_fonctions(char c, char *escaped, char *to_remove, int index);

const char		g_charset[] = "\"\'\\";
unsigned int	g_nb_remove = 0;

static inline void	set_escape(char *str, unsigned int index)
{
	*(str + index / 8) |= (1 << (index % 8));
}

char			sh_is_escape(char *str, unsigned int index)
{
	return (*(str + index / 8) & (1 << (index % 8)));
}

static void			remove_escape(char *str, char *to_remove)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
		ft_printf("%X\n", *to_remove);
	while (*str)
	{
		if (sh_is_escape(to_remove, i))
		{
			ft_printf("i=%d\n", i);
			*str = *(str + 1 + j);
//			if (!*str)
//				break ;
			j++;
			i++;
			continue ;
		}
		(*str = *(str + j));
		str++;
		i++;
	}
}

void	*sh_esc_bslash(char c, char *escaped, char *to_remove, int index)
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
		set_escape(to_remove, index);
		++g_nb_remove;
		return ((void *)fcts[(int)(res - g_charset)]);
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
	ft_strdel(&to_remove);
	return (ret);
}


int		main(void)
{
	char str[] = "\\l\\o\\\\l";
	char *l = NULL;

	ft_printf("Avant=%s|\n", str);
	sh_escape(str, &l);
	ft_printf("Apres=%s|\n", str);
}