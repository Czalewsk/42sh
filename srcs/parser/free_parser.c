/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:32:19 by maastie           #+#    #+#             */
/*   Updated: 2018/01/05 19:32:19 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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

int	ft_free_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		i++;
		free(array[i - 1]);
	}
	return (0);
}

int	ft_free_process(t_process *p)
{
	t_process *t;

	while (p)
	{
		ft_free_array(p->argv);
		t = p;
		p = p->next;
		free(t);
	}
	return (0);
}

int	ft_free_job(t_job *j)
{
	t_job *t;


	while (j)
	{
		t = j;
		ft_free_process(j->first_process);
		j = j->next;
	}
	return (0);
}