/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:06:56 by thugo             #+#    #+#             */
/*   Updated: 2018/01/12 19:33:43 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include "libft.h"

extern t_token_assign	g_token_operator[];
extern t_token_assign	g_token_reserved[];

int		rules_comment(t_token *tk, char **cur)
{
	if (**cur == '#' && !tk->size)
	{
		while (*++*cur)
			;
		return (1);
	}
	return (0);
}

int		rules_operator(t_token *tk, char **cur)
{
	int		i;
	size_t	size;

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

int		rules_reserved(t_token *tk, char **cur)
{
	int		i;
	size_t	size;

	if (tk->size)
		return (0);
	i = 0;
	while (g_token_reserved[i].op)
	{
		size = ft_strlen(g_token_reserved[i].op);
		if (!ft_strncmp(*cur, g_token_reserved[i].op, size))
		{
			tk->str = *cur;
			tk->size = size;
			tk->id = g_token_reserved[i].id;
			*cur += size;
			return (1);
		}
		++i;
	}
	return (0);
}

int		rules_io_number(t_token *tk, char **cur)
{
	int		i;

	if (tk->size)
		return (0);
	i = 0;
	while (ft_isdigit(*(*cur + i)))
		++i;
	if (i > 0 && (*(*cur + i) == '<' || *(*cur + i) == '>'))
	{
		tk->str = *cur;
		tk->size = i;
		tk->id = IO_NUMBER;
		*cur += i;
		return (1);
	}
	return (0);
}

int		rules_assignment_word(t_token *tk, char **cur)
{
	int		i;

	i = 0;
	if (!tk->size)
		return (0);
	if (**cur == '=')
	{
		if (ft_isdigit(*tk->str) || (*tk->str != '_' && !ft_isalpha(*tk->str)))
			return (0);
		while (tk->str + ++i < *cur)
			if (!ft_isalnum(*(tk->str + i)) && *(tk->str + i) != '_')
				return (0);
		tk->id = ASSIGNMENT_WORD;
	}
	return (0);
}

int		rules_word(t_token *tk, char **cur)
{
	if (**cur == ' ' || **cur == '\t' || **cur == '\n')
	{
		++*cur;
		if (tk->size)
			return (1);
	}
	else
	{
		if (!tk->size)
		{
			tk->id = WORD;
			tk->str = *cur;
		}
		++tk->size;
		++*cur;
	}
	return (0);
}

static	int (*g_rules[])(t_token *, char **) = {
	rules_comment,
	rules_operator,
	rules_reserved,
	rules_io_number,
	rules_assignment_word,
	rules_word,
	NULL
};

int			lexer_getnexttoken(t_token *tk, char **cur, char **cmd)
{
	int	i;

	ft_bzero(tk, sizeof(t_token));
	(void)cmd;
	while (**cur)
	{
		i = 0;
		while (g_rules[i])
		{
			if (g_rules[i](tk, cur) && tk->size)
			{
				if (!(tk->str = ft_strndup(tk->str, tk->size)))
					exit(EXIT_FAILURE);
				return (1);
			}
			++i;
		}
	}
	return (0);
}
