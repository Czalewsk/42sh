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

extern t_reserved				g_reserveds[];
extern t_valid					g_valids[];
extern t_excepted 				g_excepteds[];
extern t_modify					g_modifys[];

t_tree		*go_to_current_right(t_tree *cur, t_tree *new)
{
	new->father = cur;
	cur->right = new;
	return (new);
}

t_tree		*go_to_current_left(t_tree *cur, t_tree *new)
{
	t_tree	*tmp;

	tmp = cur;
	while (tmp->father)
		tmp = tmp->father;
	tmp->left = new;
	new->father = tmp;
	return (new);
}

int	check_excepted(t_tree *cur, t_tree *new)
{
	int		i;

	i = 0;
	if (cur->token.id == WORD && new->token.id == WORD)
		return (0);
	while (g_excepteds[i].one || g_excepteds[i].two)
	{
		if (g_excepteds[i].one == cur->token.id)
			if (g_excepteds[i].two == new->token.id)
				return (0);
		i++;
	}
	return (-1);
}

int	modify_id(t_tree *new)
{
	int		i;

	i = 0;
	while (g_modifys[i].id)
	{
		if (g_modifys[i].id == new->token.id)
			return (0);
		i++;
	}
	return (1);
}

t_tree						*cmpand_if(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpand(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmplpar(t_tree *cur, t_tree *new)
{
	(void)new;
	return (cur);
}

t_tree						*cmprpar(t_tree *cur, t_tree *new)
{
	(void)new;
	return (cur);
}

t_tree						*cmpdsemi(t_tree *cur, t_tree *new)
{
	(void)new;
	return (cur);
}

t_tree						*cmpsemi(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpnewline(t_tree *cur, t_tree *new)
{
	(void)new;
	return (cur);
}

t_tree						*cmpor_if(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmppipe(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpdless(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpdgreat(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmplessand(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpgreatand(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpdlessdash(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmplessgreat(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpclobber(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpless(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpgreat(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpif(t_tree *cur, t_tree *new)
{
	if (cur->token.id == WORD && modify_id(new) == 0)
		new->token.id = WORD;
	if (check_excepted(cur, new) == 0)
		return (go_to_current_left(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpthen(t_tree *cur, t_tree *new)
{
	if (cur->token.id == WORD && modify_id(new) == 0)
		new->token.id = WORD;
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpelse(t_tree *cur, t_tree *new)
{
	if (cur->token.id == WORD && modify_id(new) == 0)
		new->token.id = WORD;
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpelif(t_tree *cur, t_tree *new)
{
	if (cur->token.id == WORD && modify_id(new) == 0)
		new->token.id = WORD;
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpfi(t_tree *cur, t_tree *new)
{
	if (cur->token.id == WORD && modify_id(new) == 0)
		new->token.id = WORD;
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpdo(t_tree *cur, t_tree *new)
{

	if (cur->token.id == WORD && modify_id(new) == 0)
		new->token.id = WORD;
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpdone(t_tree *cur, t_tree *new)
{
	if (cur->token.id == WORD && modify_id(new) == 0)
		new->token.id = WORD;
	if (check_excepted(cur, new) == 0)
		return (go_to_current_right(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpcase(t_tree *cur, t_tree *new)
{
	(void)new;
	return (cur);
}

t_tree						*cmpesac(t_tree *cur, t_tree *new)
{
	(void)new;
	return (cur);
}

t_tree						*cmpwhile(t_tree *cur, t_tree *new)
{
	if (cur->token.id == WORD && modify_id(new) == 0)
		new->token.id = WORD;
	if (check_excepted(cur, new) == 0)
		return (go_to_current_left(cur, new));
	free(new);
	return (NULL);
}

t_tree						*cmpuntil(t_tree *cur, t_tree *new)
{
	(void)new;
	return (cur);
}

t_tree						*cmpfor(t_tree *cur, t_tree *new)
{
	(void)new;
	return (cur);
}

t_tree						*cmpword(t_tree *cur, t_tree *new)
{
	if (check_excepted(cur, new) == 0)
	{
		if ((!imb || (imb && imb->end_of_reserved != NULL)) && cur->token.id == SEMI)
			return (go_to_current_left(cur, new));
		return (go_to_current_right(cur, new));
	}
	free(new);
	return (NULL);
}