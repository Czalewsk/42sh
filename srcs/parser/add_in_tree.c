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

// void		set_new_id(t_tree *cur, t_tree *new)
// {
// 	t_token_id	o;
// 	t_token_id	n;

// 	o = cur->token.id;
// 	n = new->token.id;
// 	if (n == While || n == If || n == Case || n == Until)
// 	{
// 		if (o != AND && o != SEMI && o != OR_IF
// 			&& o != AND_IF && o != AND)
// 			new->token.id = WORD;
// 	}
// 	// else if (o == IO_NUMBER) // check sur les operateur et non pas les IO_NUMBER
// 	// {
// 	// 	if (n != DLESS && n != DGREAT && n != LESSGREAT && n != GREATAND
// 	// 		&& n != DLESSDASH && n != CLOBBER && n != LESS && n != GREAT)
// 	// 		new->token.id = WORD;
// 	// }
// }

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
		t == LESSGREAT || t == DLESS || t == DGREAT)
		return (-1);
	return (0);
}

int				cnewline(t_token t, char **cmd, char *cur)
{
	free(t.str);
	if (!head_tree || !current)
		return (0);
	else if (check_last_token(current) == -1)
		return (-1);
	else if (current->token.id == OR_IF || current->token.id == AND_IF)
		return (read_from_prompt(cmd, cur));
	return (0);
}

int			add_in_classic_tree(t_tree *cur, t_tree *new)
{
	int		i;

	i = 0;
//	set_new_id(cur, new);
	while (g_classics[i].cmp)
	{
		if (cur->token.id == g_classics[i].one && 
			new->token.id == g_classics[i].two)
		{
			if ((current = g_classics[i].cmp(cur, new)) == NULL)
				return (ft_free_node(new));
			return (0);
		}
		i++;
	}
	return (ft_free_node(new));
}
