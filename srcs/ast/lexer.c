/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:37:06 by thugo             #+#    #+#             */
/*   Updated: 2017/11/26 19:37:16 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "debug.h"
#include "libft.h"

static const t_operator	g_operator[] = {
	{"&&", AND_IF},
	{"&", AND},
	{"(", LPAR},
	{")", RPAR},
	{";;", DSEMI},
	{";", SEMI},
	{"\n", NEWLINE},
	{"||", OR_IF},
	{"|", PIPE},
	{"<<", DLESS},
	{">>", DGREAT},
	{"<&", LESSAND},
	{">&", GREATAND},
	{"<<-", DLESSDASH},
	{"<>", LESSGREAT},
	{">|", CLOBBER},
	{"<", LESS},
	{">", GREAT},
	{NULL, 0}
};

static int				get_operator(char **cur, t_token *token)
{
	int		i;
	size_t	size;

	i = 0;
	while (g_operator[i].op)
	{
		size = ft_strlen(g_operator[i].op);
		if (!ft_strncmp(*cur, g_operator[i].op, size))
		{
			if (token->size)
				return (1);
			token->size = size;
			token->id = g_operator[i].id;
			*cur += size;
			return (1);
		}
		++i;
	}
	return (0);
}

static t_token			*next_token(char **cur)
{
	t_token		*token;

	token = NULL;
	while (**cur)
	{
		if (**cur == ' ' || **cur == '\t')
		{
			if (token && token->begin)
				return (token);
		}
		else
		{
			if (!token)
			{
				if (!(token = (t_token *)ft_memalloc(sizeof(t_token))))
					exit(EXIT_FAILURE);
				token->begin = *cur;
			}
			if (get_operator(cur, token))
				return (token);
			++(token->size);
		}
		++(*cur);
	}
	return (token);
}

t_list					*lexer_tokenize(char *cmd)
{
	t_list		*lst;
	t_list		*item;
	t_token		*token;

	lst = NULL;
	while ((token = next_token(&cmd)))
	{
		if (!(item = ft_lstnew((void *)token, sizeof(t_token))))
			exit(EXIT_FAILURE);
		ft_lstaddback(&lst, item);
		free(token);
	}
	return (lst);
}
