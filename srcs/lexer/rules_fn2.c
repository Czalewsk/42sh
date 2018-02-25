/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_fn2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:44:48 by thugo             #+#    #+#             */
/*   Updated: 2018/01/29 21:16:26 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_types.h"
#include "libft.h"

int		rules_word(t_token *tk, char **cur, char *escape)
{
	if (!*escape && (**cur == ' ' || **cur == '\t' || **cur == '\n'))
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

/*
**	Flags:
**		 1: Simple quote '
**		 2: Double quote "
**		 4: Backslash \
**		 8: Backslash counter
**		16: Backquote `
*/

int		rules_escape(t_token *tk, char **cur, char *escape)
{
	(void)tk;
	if (*escape & 8)
	{
		if (**cur != '\n')
			*escape &= ~(char)8;
	}
	else if (*escape & 4)
		*escape &= ~(char)4;
	if (!(*escape & (char)(2 | 4 | 16)) && **cur == '\'')
		*escape ^= 1;
	else if (!(*escape & (char)(1 | 4 | 16)) && **cur == '"')
		*escape ^= 2;
	else if (!(*escape & (char)(1 | 4)) && **cur == '\\')
		*escape |= (char)(4 | 8);
	else if (!(*escape & (char)(1 | 2 | 4)) && **cur == '`')
		*escape ^= 16;
	return (0);
}

int		rules_subsh(t_token *tk, char **cur, char *escape)
{
	if (*escape & 4)
		return (0);
	if (**cur == '`' && *escape & 16 && tk->size)
		return (1);
	else if (**cur == '`' && !(*escape & 16))
	{
		++*cur;
		++tk->size;
		tk->id = SUBSH;
		return (1);
	}
	return (0);
}

/* OLD VERSION */
/*
int		rules_param_exp(t_token *tk, char **cur, char *escape)
{
	int		i;

	if (*escape & ~(char)2 || **cur != '$')
		return (0);
	i = 1;
	while (*cur + i && (ft_isalnum(*(*cur + i)) || *(*cur + i) == '_'))
		++i;
	if (i > 1)
	{
		if (tk->size)
			return (1);
		tk->size = i;
		tk->str = *cur;
		tk->id = PARAM_EXP;
		*cur += i;
		return (1);
	}
	return (0);
}*/

