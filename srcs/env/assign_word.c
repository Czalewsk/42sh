/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 16:48:43 by thugo             #+#    #+#             */
/*   Updated: 2018/03/07 13:25:02 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree	*assign_word(t_process *p, t_tree *c)
{
	char	type;
	char	*name;
	char	*value;
	t_tree	*cur;

	(void)p;
	type = ENV_LOCAL;
	value = ft_strchr(c->token.str, '=') + 1;
	name = ft_strndup(c->token.str, (size_t)(value - (c->token.str + 1)));
	cur = c;
	while (cur)
	{
		if (cur->token.id == WORD)
		{
			type = ENV_TEMP;
			break ;
		}
		cur = cur->right;
	}
	env_set(name, value, type);
	free(name);
	return (c->right);
}
