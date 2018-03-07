/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 16:48:43 by thugo             #+#    #+#             */
/*   Updated: 2018/03/05 20:13:05 by thugo            ###   ########.fr       */
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
	ft_printf("Name: %s | Value: %s | Type: %i\n", name, value, (int)type);
	free(name);
	return (c->right);
}

/*t_tree	*clear_assign_word(t_tree *cur, t_tree *new)
{
	ft_printf("Cur: %s | id: %i\n", cur->token.str, cur->token.id);
	ft_printf("New: %s | id: %i\n", new->token.str, new->token.id);
	//cur->right = new;
	//new->previous = cur;
	new->token.id = WORD;
	return (go_to_current_right(cur, new));
}*/
