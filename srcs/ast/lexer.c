/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:37:06 by thugo             #+#    #+#             */
/*   Updated: 2017/11/30 14:47:53 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include "libft.h"

extern t_astrule		g_astrules[];

/*
**	Assigne le premier token trouve depuis **cur dans le param token.
**
**	La fonction va deplacer le pointeur **cur dans la fonction appelante.
**
**	Retourne:
**		 0 si plus rien a lire.
**		 1 si un nouveau token a ete trouve.
**		-1 si l'utilisateur a fait la combinaison ctrl+d.
**		-2 si l'utilisateur a fait la combinaison ctrl+c.
**		-3 erreur de malloc.
*/

int						lexer_getnexttoken(t_token *token, char **cur)
{
	size_t		size;

	bzero(token, sizeof(t_token));
	size = 0;
	while (**cur)
	{
		if ((**cur == ' ' || **cur == '\t') && token->str)
			return ((token->str = ft_strndup(token->str, size)) ? 1 : -3);
		else if (**cur != ' ' && **cur != '\t')
		{
			if (!token->str)
				token->str = *cur;
			if (lexer_tokenize(token, cur, &size))
				return ((token->str = ft_strndup(token->str, size)) ? 1 : -3);
			++size;
		}
		++(*cur);
	}
	if (!token->str)
		return (0);
	return ((token->str = ft_strndup(token->str, size)) ? 1 : -3);
}
