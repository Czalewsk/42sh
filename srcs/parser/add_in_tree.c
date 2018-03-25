/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_in_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:32:06 by maastie           #+#    #+#             */
/*   Updated: 2018/03/21 14:07:46 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern t_classic					g_classics[];

t_tree			*go_to_current_right(t_tree *cur, t_tree *new)
{
	new->previous = cur;
	cur->right = new;
	return (new);
}

t_tree			*go_to_current_left(t_tree *cur, t_tree *new)
{
	t_tree	*tmp;

	tmp = cur;
	while (tmp->previous)
		tmp = tmp->previous;
	tmp->left = new;
	new->father = tmp;
	return (new);
}

int				check_last_token(t_tree *cur)
{
	t_token_id	t;

	t = cur->token.id;
	if (t == GREAT || t == LESS || t == LESSAND || t == GREATAND ||
		t == LESSGREAT || t == DLESS || t == DGREAT || t == ANDGREAT)
		return (-1);
	return (0);
}

int				cnewline(t_token t, char **cmd, char **cur)
{
	int			new_line_call;

	if (t.str && t.str != NULL)
		free(t.str);
	if (!g_head_tree || !g_current)
		return (0);
	else if (check_last_token(g_current) == -1)
		return (-1);
	else if (g_current->token.id == OR_IF ||
		g_current->token.id == AND_IF || g_current->token.id == PIPE)
		while ((new_line_call = read_from_prompt(cmd, cur)))
		{
			if (new_line_call == -1 || new_line_call == -3)
				return (-1);
			if (new_line_call == -2)
				break ;
		}
	return (0);
}

int				add_in_classic_tree(t_tree *cur, t_tree *new)
{
	int			i;

	if (new->token.id == ASSIGNMENT_WORD)
		clear_assign_word(cur, new);
	i = 0;
	while (g_classics[i].cmp)
	{
		if (cur->token.id == g_classics[i].one &&
			new->token.id == g_classics[i].two)
		{
			if ((g_current = g_classics[i].cmp(cur, new)) == (void *)1)
				return (ft_free_node(new));
			DEBUG("%p|%s|\n", g_current, g_current->token.str);
			if (g_classics[i].here)
			{
				if ((g_classics[i].here(cur, new)) == (void *)1)
					return (-2);
			}
			return (0);
		}
		i++;
	}
	return (ft_free_node(new));
}
