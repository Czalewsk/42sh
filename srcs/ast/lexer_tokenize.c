/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:53:08 by thugo             #+#    #+#             */
/*   Updated: 2017/11/30 14:57:26 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_types.h"
#include "libft.h"

extern t_astrule		g_astrules[];

static int	tokenize_operator(t_token *token, char **cur, size_t *cursize)
{
	int		i;
	size_t	size;

	i = 0;
	while (g_astrules[i].op)
	{
		if (g_astrules[i].type == OPERATOR)
		{
			size = ft_strlen(g_astrules[i].op);
			if (!ft_strncmp(*cur, g_astrules[i].op, size))
			{
				if (*cursize)
					return (1);
				*cursize = size;
				token->id = g_astrules[i].id;
				*cur += size;
				return (1);
			}
		}
		++i;
	}
	return (0);
}

static int	tokenize_reserved(t_token *token, char **cur, size_t *cursize)
{
	int		i;
	size_t	size;

	i = 0;
	while (g_astrules[i].op)
	{
		if (g_astrules[i].type == RESERVED)
		{
			size = ft_strlen(g_astrules[i].op);
			if (!ft_strncmp(*cur, g_astrules[i].op, size))
			{
				if (*cursize)
					return (1);
				*cursize = size;
				token->id = g_astrules[i].id;
				*cur += size;
				return (1);
			}
		}
		++i;
	}
	return (0);
}

int			lexer_tokenize(t_token *token, char **cur, size_t *cursize)
{
	(void)tokenize_reserved;
	if (tokenize_operator(token, cur, cursize) == 1)
		return (1);
	return (tokenize_reserved(token, cur, cursize));
}
