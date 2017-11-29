/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:37:06 by thugo             #+#    #+#             */
/*   Updated: 2017/11/29 11:33:45 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast_types.h"
#include "libft.h"

extern t_astrule g_astrules[];

static int				get_operator(char **cur, t_token *token)
{
	int		i;
	size_t	size;

	i = 0;
	while (g_astrules[i].op)
	{
		size = ft_strlen(g_astrules[i].op);
		if (!ft_strncmp(*cur, g_astrules[i].op, size))
		{
			if (token->size)
				return (1);
			token->size = size;
			token->id = g_astrules[i].id;
			*cur += size;
			return (1);
		}
		++i;
	}
	return (0);
}

/*
**	Assigne le premier token trouve depuis **cur dans le param token.
**
**	La structure token devra etre initialise a NULL a chaque appel de la
**		fonction.
**	La fonction va deplacer le pointeur **cur dans la fonction appelante.
**
**	Retourne:
**		-2 si tout c'est bien passe.
**		-1 si l'utilisateur a fait la combinaison ctrl+d.
**		-3 si l'utilisateur a fait la combinaison ctrl+c.
*/

int						lexer_getnexttoken(t_token *token, char **cur)
{
	while (**cur)
	{
		if ((**cur == ' ' || **cur == '\t') && token->begin)
			return (-2);
		else if (**cur != ' ' && **cur != '\t')
		{
			if (!token->begin)
				token->begin = *cur;
			if (get_operator(cur, token))
				return (-2);
			++(token->size);
		}
		++(*cur);
	}
	return (-2);
}
