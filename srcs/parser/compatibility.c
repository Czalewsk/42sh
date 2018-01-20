/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compatibility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:08:24 by maastie           #+#    #+#             */
/*   Updated: 2017/12/14 16:08:25 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree		*go_to_current_right(t_tree *cur, t_tree *new)
{
	new->previous = cur;
	cur->right = new;
	return (new);
}

t_tree		*go_to_current_left(t_tree *cur, t_tree *new)
{
	t_tree	*tmp;

	tmp = cur;
	while (tmp->previous)
		tmp = tmp->previous;
	tmp->left = new;
	new->father = tmp;
	return (new);
}

int		check_last_token(t_tree *cur)
{
	t_token_id t;

	t = cur->token.id;
	if (t == GREAT || t == LESS || t == LESSAND || t == GREATAND ||
		t == LESSGREAT || t == DLESS || t == DGREAT)
		return (-1);
	return (0);
}

int			cnewline(t_token t, char **cmd, char *cur)
{
	free(t.str);
	if (!head_tree || !current)
		return (0);
	else if (check_last_token(current) == -1)
		return (-1);
	else
	{
		//if (in_reserved() == 0)
		// change id to SEMI, and let`s see compTree
		//else 
		// free(t.str);
		// t.str = ft_strdup(";");
		// t.id = SEMI;
		if (current->token.id == OR_IF || current->token.id == AND_IF)
			return (read_from_prompt(cmd, cur));
	}
	return (0);
}