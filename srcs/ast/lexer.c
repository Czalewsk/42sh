/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:06:56 by thugo             #+#    #+#             */
/*   Updated: 2018/01/12 14:24:56 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include "libft.h"

extern t_token_assign	g_token_operator[];
extern t_token_assign	g_token_reserved[];

int		rules_comment(t_token *tk, char **cmd, char **cur)
{
	(void)cmd;
	if (**cur == '#' && !tk->size)
	{
		while (++**cur)
			;
		return (1);
	}
	return (0);
}

int		rules_operator(t_token *tk, char **cmd, char **cur)
{
	int		i;
	size_t	size;

	(void)cmd;
	i = 0;
	while (g_token_operator[i].op)
	{
		size = ft_strlen(g_token_operator[i].op);
		if (!ft_strncmp(*cur, g_token_operator[i].op, size))
		{
			if (tk->size)
				return (1);
			tk->str = *cur;
			tk->size = size;
			tk->id = g_token_operator[i].id;
			*cur += size;
			return (1);
		}
		++i;
	}
	return (0);
}

int		rules_word(t_token *tk, char **cur, char **cmd)
{
	(void)cmd;
	if (**cur == ' ' || **cur == '\t' || **cur == '\n')
	{
		++*cur;
		if (tk->size)
		{
			tk->id = WORD;
			return (1);
		}
	}
	else
	{
		if (!tk->size)
			tk->str = *cur;
		++tk->size;
		++*cur;
	}
	return (0);
}

static	int (*g_rules[])(t_token *, char **, char **) = {
	rules_comment,
	rules_operator,
	rules_word,
	NULL
};

int			lexer_getnexttoken(t_token *tk, char **cmd, char **cur)
{
	int	i;

	i = 0;
	ft_bzero(tk, sizeof(t_token));
	(void)cmd;
	while (**cur)
	{
		while (g_rules[i])
		{
			if (g_rules[i](tk, cmd, cur) && tk->size)
			{
				if (!(tk->str = ft_strndup(tk->str, tk->size)))
					exit(EXIT_FAILURE);
				return (1);
			}
			++i;
		}
		++tk->size;
		++*cur;
	}
	return (0);
}
