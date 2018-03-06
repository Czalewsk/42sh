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
	(void)p;
	return (c->right);
}

t_tree	*clear_assign_word(t_tree *cur, t_tree *new)
{
	t_tree	*tmp;
	new->previous = cur;
	cur->right = new;
	tmp = new;
	ft_printf("New: %s | NewTk: %i\n", new->token.str, new->token.id);
	while (tmp && tmp->token.id == ASSIGNMENT_WORD)
	{
		tmp->token.id = WORD;
		tmp = tmp->right;
	}
	return (cur);
}
