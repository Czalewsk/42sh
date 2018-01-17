/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_fn2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:44:48 by thugo             #+#    #+#             */
/*   Updated: 2018/01/17 17:45:04 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_types.h"

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
