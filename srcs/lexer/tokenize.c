/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:41:53 by thugo             #+#    #+#             */
/*   Updated: 2018/01/17 17:49:34 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"

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
