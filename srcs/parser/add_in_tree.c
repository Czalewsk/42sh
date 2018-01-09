/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_in_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:32:06 by maastie           #+#    #+#             */
/*   Updated: 2018/01/05 19:32:06 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern t_classic					g_classics[];
extern t_reserved					g_reserveds[];

void		set_new_id(t_tree *cur, t_tree *new)
{
	int		i;

	i = 0;
	while (g_reserveds[i].res)
	{
		if (new->token.id == g_reserveds[i].one)
		{
			if (cur->token.id != AND && cur->token.id != SEMI
				&& cur->token.id != OR_IF && cur->token.id != AND_IF
				&& cur->token.id != AND)
				new->token.id = WORD;
		}
		i++;
	}
}

int			add_in_classic_tree(t_tree *cur, t_tree *new)
{
	int		i;

	i = 0;
	set_new_id(cur, new);
	while (g_classics[i].cmp)
	{
		if (cur->token.id == g_classics[i].one && 
			new->token.id == g_classics[i].two)
		{
			if ((current = g_classics[i].cmp(cur, new)) == NULL)
				return (-4);
			return (0);
		}
		i++;
	}
	return (-4);
}
