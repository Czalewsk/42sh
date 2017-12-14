/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:30:59 by maastie           #+#    #+#             */
/*   Updated: 2017/11/26 18:31:01 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern t_compatibilitytree		g_compatibilitytrees[];


void	ft_free_tree(t_tree *c)
{
	t_tree *r;
	t_tree *tmp;

	if (c->left)
		ft_free_tree(c->left);
	r = c;
	while (r)
	{
		tmp = r;
		free(tmp->token.str);
		free(tmp);
		r = r->right;
	}	
}

void	ft_affiche(t_tree *c)
{
	t_tree *r;

	if (c->left)
		ft_affiche(c->left);
	r = c;
	while (r)
	{
		DEBUG("%s\n", r->token.str);
		r = r->right;
	}
}

t_tree	*init_node(t_token c, t_tree *n)
{
	if ((n = (t_tree *)malloc(sizeof(t_tree))) == NULL)
		return (NULL);
	n->father = NULL;
	n->right = NULL;
	n->left = NULL;
	n->token = c;
	return (n);
}

// The first word following one of the reserved words other than case, for, or in
// The third word in a case command (only in is valid in this case)
// The third word in a for command (only in and do are valid in this case)
// check sur les prio -> head, head left, head righ si head left is a reserved
// else fill right

int		add_in_tree(t_token t)
{
	int		i;

	i = 0;
	while (g_compatibilitytrees[i].cmp)
	{
		// DEBUG("Token: %i | Comp: %i\n", t.id, g_compatibilitytrees[i].id);
		if (t.id == g_compatibilitytrees[i].id)
		{
			// DEBUG("%s|%i\n", t.str, t.id);
			if ((current = g_compatibilitytrees[i].cmp(current, t)) == NULL)
			{
				DEBUG("Error parsing add in tree near `%s\n'", t.str);
				free(t.str);
				return (-4);
			}
			return (0);
		}
		i++;
	}
	return (0);
}

int		place_token(t_token t)
{
	if (!head_tree)
	{
		if (t.id == NEWLINE)
			return (0);
		if (t.id != SEMI && t.id != WORD)
		{
			DEBUG("Error parsing head near `%s\n'", t.str);
			free(t.str);
			return (-1);
		}
		else if ((head_tree = init_node(t, head_tree)) == NULL)
			return (-3);
		current = head_tree;
		current->father = head_tree;
		return (0);
	}
	return (add_in_tree(t));
}

int		check_last_token(t_tree *current)
{
	if (current->token.id == AND_IF || current->token.id == OR_IF ||
		current->token.id == GREAT || current->token.id == LESS ||
		current->token.id == LESSAND || current->token.id == GREATAND ||
		current->token.id == LESSGREAT || current->token.id == DLESS ||
		current->token.id == DGREAT)
	{
		DEBUG("Error parsing last near `\\n' \n");
		ft_free_tree(head_tree);
		return (-1);		
	}
	return (0);
}

int		parser(char *cmd)
{
	int	ret;
	t_token	t;
	char *cur;

	cur = cmd;
	head_tree = NULL;
	while ((ret = lexer_getnexttoken(&t, &cmd, &cur)) != 0)
	{
		// if (ret < 0)
		// 	return (-1);
		// else if (place_token(t) < 0)
		// 	return (-4);
	}
	if (head_tree)
	{
		if (check_last_token(current) != 0)
			return (-1);
		ft_affiche(head_tree);
		ft_free_tree(head_tree);
	}
	return (0);
}