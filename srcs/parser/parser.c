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
extern t_reserved				g_reserveds[];
extern t_close_imb				g_close_imbs[];
//extern t_valid					g_valids[];


// 					LEAKS
		// ctrl c en boucle

int	ft_free_token(t_tree *token)
{
	free(token);
	return (-1);
}

int	ft_free_tree(t_tree *c)
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
		r = r->right;
		free(tmp);
	}
	return (0);
}

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
	ft_printf("\nEnd of right");
	if (c->left)
		ft_affiche(c->left);
}

t_imb		*init_imb(t_imb *n)
{
	if ((n = (t_imb *)malloc(sizeof(t_imb))) == NULL)
		return (NULL);
	n->old = NULL;
	n->next = NULL;
	n->reserved_node = NULL;
	n->end_of_reserved = NULL;
	return (n);
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

t_imb		*is_a_first_reserved(t_imb *imb, t_tree *cur)
{
	t_imb 	*n;
	int		i;

	n = NULL;
	i = 0;
	if (imb && imb->reserved_node)
		return (imb);
	while (g_reserveds[i].id)
	{
		if (cur->token.id == g_reserveds[i].id)
		{
			if (imb)
			{
				n = init_imb(n);
				n->reserved_node = cur;
				imb->next = n;
				n->old = imb;
				imb = n;
				return (n);
			}
			imb = init_imb(imb);
			imb->reserved_node = cur;
			return (imb);
		}
		i++;
	}
	return (imb);
}

t_imb		*is_a_close_reserved(t_imb *imb, t_tree *cur)
{
	t_imb 	*n;
	int		i;

	n = NULL;
	i = 0;
	if (!imb || (imb && imb->end_of_reserved))
		return (imb);
	while (g_reserveds[i].id)
	{
		if (g_reserveds[i].id == imb->reserved_node->token.id)
		{
			if (g_reserveds[i].end_id == cur->token.id)
			{
				imb->end_of_reserved = cur;
				if (imb->old)
					imb = imb->old;
				current = imb->reserved_node;
			}
			return (imb);
		}
		i++;
	}
	return (imb);
}

int		add_in_tree(t_tree *cur, t_tree *new)
{
	int		i;

	i = 0;
	while (g_compatibilitytrees[i].cmp)
	{
		if (new->token.id == g_compatibilitytrees[i].id)
		{
			if ((current = g_compatibilitytrees[i].cmp(cur, new)) == NULL)
				return (-4);
			return (0);
		}
		i++;
	}
	return (0);
}

int		add_in_imb(t_imb *imb, t_tree *new)
{
	t_tree *cur;

	cur = imb->reserved_node;
	while (cur->right)
		cur = cur->right;
	return (add_in_tree(cur, new));
}

int		add_by_imb(t_imb *imb, t_tree *new)
{
	t_tree		*tmp;
	int			i;

	i = 0;
	tmp = imb->reserved_node;
	while (g_close_imbs[i].one)
	{
		if (g_close_imbs[i].one == tmp->token.id)
		{
			while (tmp->right)
			{
				if (g_close_imbs[i].two == tmp->token.id)
				{
					if (g_close_imbs[i].two == new->token.id)
						return (ft_free_token(new));
					return (add_in_imb(imb, new));
				}
				tmp = tmp->right;
			}
		}
		i++;
	}
	return (add_in_imb(imb, new));
}

int		place_token(t_token t)
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
	if (imb && imb->end_of_reserved != NULL)
		return (add_by_imb(imb, n));
	// cas ou le current est perdu check depuis head
	return (add_in_tree(current, n));
}

int		check_last_token(t_tree *cur)
{
	if (cur->token.id == GREAT || cur->token.id == LESS ||
		cur->token.id == LESSAND || cur->token.id == GREATAND ||
		cur->token.id == LESSGREAT || cur->token.id == DLESS ||
		current->token.id == DGREAT)
		return (-1);
	return (0);
}

int		parser(char *cmd)
{
	int	ret;
	char *cur;
	t_token	t;

	cur = cmd;
	head_tree = NULL;
	imb = NULL;
	while ((ret = lexer_getnexttoken(&t, &cmd, &cur)) != 0)
	{
		if (ret < 0)
			return (-1);
		else if (place_token(t) < 0)
		{
			ft_printf("\nError parsing near `%s' PLACE TOKEN\n", t.str);
			free(t.str);
			ft_affiche(head_tree);
			if (head_tree)
				return (ft_free_tree(head_tree));
		}
		imb = is_a_first_reserved(imb, current);
		imb = is_a_close_reserved(imb, current);
	}
	if (imb && imb->end_of_reserved == NULL)
		ft_printf("\nError parsing need to complete this TOKEN %s\n", imb->reserved_node->token.str);
	if (head_tree)
	{
		if (check_last_token(current) != 0)
			ft_printf("\nError parsing near `%s' LAST\n", current->token.str);
		else
			ft_affiche(head_tree);
		return (ft_free_tree(head_tree));
	}
	return (0);
}