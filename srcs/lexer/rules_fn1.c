/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_fn1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:44:16 by thugo             #+#    #+#             */
/*   Updated: 2018/01/17 17:48:53 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
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
