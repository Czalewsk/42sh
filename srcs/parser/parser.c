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

extern t_valid_res	g_valid_ress[];

void	ft_affiche(t_tree *c)
{
	t_tree *r;

	r = c;
	ft_printf("\nHead of branch = %s", c->token.str);
	while (r)
	{
		r = r->right;
		if (r)
			ft_printf("\n%s", r->token.str);
	}
	if (c->left)
		ft_affiche(c->left);
}

t_tree	*init_node(t_token c, t_tree *n)
{
	if ((n = (t_tree *)malloc(sizeof(t_tree))) == NULL)
		return (NULL);
	n->previous = NULL;
	n->father = NULL;
	n->right = NULL;
	n->left = NULL;
	n->token = c;
	return (n);
}

int		check_for_reserved(t_tree *c, char *cur, char *cmd)
{
	int	i;

	i = 0;
	while (g_reserveds[i].res)
	{
		if (g_reserveds[i].one == c->token.id)
			return ()
		i++;
	}
	return (0);
}

int		place_token(t_token t, char *cur, char *cmd)
{
	t_tree	*n;

	n = NULL;
	if (!head_tree)
	{
		if (t.id == NEWLINE)
			return (0);
		if (t.id != WORD && t.id != LPAR && t.id != If && t.id != While
			&& t.id != Until && t.id != Case)
			return (-1);
		else if ((head_tree = init_node(t, head_tree)) == NULL)
			return (-3);
		current = head_tree;
		return (0);
	}
	n = init_node(t, n);
	return (add_in_classic_tree(current, n));
}

int		check_last_token(t_tree *cur)// a modifier pour un rappel a promptadd
{
	if (cur->token.id == GREAT || cur->token.id == LESS ||
		cur->token.id == LESSAND || cur->token.id == GREATAND ||
		cur->token.id == LESSGREAT || cur->token.id == DLESS ||
		current->token.id == DGREAT || current->token.id == AND ||
		current->token.id == OR_IF || current->token.id == AND_IF)
			return (-1);
	return (0);
}

int		cur_is_new_res(t_tree *cur)
{
	int	i;

	i = 0;
	while (g_valid_ress[i].two)
	{
		if (g_valid_ress[i].two == cur->token.id)
		{
			if (!cur->previous ||
				(cur->previous && cur->previous->token.id == g_valid_ress[i].one))
				return (0);
		}
		i++;
	}
	return (1);
}

int		parser(char *cmd)
{
	int	ret;
	char *cur;
	t_token	t;

	cur = cmd;
	head_tree = NULL;
	while ((ret = lexer_getnexttoken(&t, &cmd, &cur)) != 0)
	{
		if (ret < 0)
			return (-1);
		if (place_token(t, cur, cmd) < 0)
		{
			ft_printf("\nError parsing near `%s' PLACE TOKEN\n", t.str);
			free(t.str);
			if (head_tree)
				ft_affiche(head_tree);
			if (head_tree)
				return (ft_free_tree(head_tree));
			return (-1);
		}
		if (cur_is_new_res(current) == 0)
		 	if (read_for_reserved(current, cur, cmd) == -1)
		 	{
		 		// dont forget to free and send error message
		 		return (-1);
		 	}

	}
	if (head_tree)
	{
		if (check_last_token(current) != 0)
			ft_printf("\nError parsing near `\\n' LAST\n", current->token.str);
		else
			ft_affiche(head_tree);
		return (ft_free_tree(head_tree));
	}
	return (0);
}