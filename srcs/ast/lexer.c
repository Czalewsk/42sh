/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:37:06 by thugo             #+#    #+#             */
/*   Updated: 2017/12/07 14:02:32 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include "prompt.h"
#include "libft.h"

extern t_astrule			g_astrules[];

static int					is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

/*
**	Flags:
**		1: Simple quote '
**		2: Double quote "
**		4: Backslash \
**		8: Backslash counter
*/

static void					quote_check(char *qstat, char **cur)
{
	if (*qstat & 8)
	{
		if (**cur != '\n')
			*qstat &= ~(char)8;
	}
	else if (*qstat & 4)
		*qstat &= ~(char)4;
	if (!(*qstat & (char)(2 | 4)) && **cur == '\'')
		*qstat ^= 1;
	else if (!(*qstat & (char)(1 | 4)) && **cur == '"')
		*qstat ^= 2;
	else if (!(*qstat & (char)(1 | 4)) && **cur == '\\')
		*qstat |= (char)(4 | 8);
}

/*
**	Retour de prompt_add:
**		-3: ctrl + c
**		-1: ctrl + d
**		-2: Normal
*/

static int					quote_finish(t_token *token, char *qstat,
								char **cmd, char **cur)
{
	char	ret;
	char	*new;
	char	prompt[10];

	if (!(*qstat & ~(char)4))
		return (1);
	if (*qstat & 8)
		*(*cur - 2) = '\0';
	ft_strcpy(prompt, *qstat & 1 ? "quote> " : "dquote> ");
	if ((ret = prompt_add(*qstat & 8 ? "> " : prompt, &new)) == -2)
	{
		if (!(new = ft_strjoin_free(*cur - token->size, new, 1)))
			exit(EXIT_FAILURE);
		if (*qstat & 8)
			token->size -= 2;
		*qstat &= ~(char)(8 | 4);
		free(*cmd);
		token->str = new;
		*cmd = new;
		*cur = new + token->size;
		return (0);
	}
	free(new);
	return (ret == -1 ? -1 : -2);
}

/*
**	Assigne le premier token trouve depuis **cur dans le param token.
**
**	La fonction va deplacer le pointeur **cur de la fonction appelante.
**
**	Retourne:
**		 0 si plus rien a lire.
**		 1 si un nouveau token a ete trouve. (La chaine token->str est malloc)
**		-1 si l'utilisateur a fait la combinaison ctrl+d.
**		-2 si l'utilisateur a fait la combinaison ctrl+c.
**		-3 erreur de malloc.
*/

int							lexer_getnexttoken(t_token *tk, char **cmd,
							char **cur)
{
	char		qstat;
	int			ret;

	bzero(tk, sizeof(t_token));
	qstat = 0;
	while (**cur || !(ret = quote_finish(tk, &qstat, cmd, cur)))
	{
		quote_check(&qstat, cur);
		if (!qstat && is_blank(**cur) && tk->size)
			return ((tk->str = ft_strndup(tk->str, tk->size)) ? 1 : -3);
		else if (qstat || !is_blank(**cur))
		{
			if (!tk->str)
				tk->str = *cur;
			if (!qstat && lexer_tokenize(tk, cur, &tk->size))
				return ((tk->str = ft_strndup(tk->str, tk->size)) ? 1 : -3);
			++tk->size;
		}
		if (**cur)
			++(*cur);
	}
	if (!tk->size || ret < 0)
		return (ret < 0 ? ret : 0);
	return ((tk->str = ft_strndup(tk->str, tk->size)) ? 1 : -3);
}
