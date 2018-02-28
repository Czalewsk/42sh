/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:41:53 by thugo             #+#    #+#             */
/*   Updated: 2018/01/29 21:13:15 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"
#include "prompt.h"

static	int (*g_rules[])(t_token *, char **, char *) = {
	rules_escape,
	rules_comment,
	rules_operator,
	rules_reserved,
	rules_io_number,
	rules_assignment_word,
	rules_subsh,
	rules_word,
	NULL
};

/*
**	Retour de prompt_add:
**		-3: ctrl + c
**		-1: ctrl + d
**		-2: Normal
**
**	Retour de quote_finish:
**		 1: Quote ok
**		 0: Quote non terminee
**		-1: ctrl + c
**		-2: ctrl + d
*/

static int	quote_finish(t_token *token, char *escape, char **cmd,
					char **cur)
{
	char	ret;
	char	*new;
	char	prompt[10];

	if (!(*escape & ~(char)4))
		return (1);
	if (*escape & 8)
		*(*cur - 2) = '\0';
	ft_strcpy(prompt, *escape & 1 ? "quote> " : "> ");
	if ((ret = prompt_add(*escape & 2 ? "dquote> " : prompt, &new, 0)) == -2)
	{
		if (!(new = ft_strjoin_free(*cur - token->size, new, 1)))
			exit(EXIT_FAILURE);
		if (*escape & 8)
			token->size -= 2;
		*escape &= ~(char)(8 | 4);
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
** 	Assigne le premier token trouve depuis **cur dans *tk.
** 	La fonction va deplacer le pointeur **cur de la fonction appelante.
**
** 	Retourne:
**		 0: si plus rien a lire.
**		 1: si un nouveau token a ete trouve. (La chaine token->str est malloc
**			et doit etre free)
**		-1: ctrl + c
**		-2: ctrl + d
*/

int			lexer_getnexttoken(t_token *tk, char **cur, char **cmd)
{
	int		i;
	char	escape;
	int		ret;

	escape = 0;
	ret = 0;
	ft_bzero(tk, sizeof(t_token));
	while (**cur || !(ret = quote_finish(tk, &escape, cmd, cur)))
	{
		i = 0;
		while (g_rules[i])
		{
			if (g_rules[i](tk, cur, &escape) && tk->size)
			{
				if (!(tk->str = ft_strndup(tk->str, tk->size)))
					exit(EXIT_FAILURE);
				return (1);
			}
			++i;
		}
	}
	return (ret == 1 ? 0 : ret);
}
