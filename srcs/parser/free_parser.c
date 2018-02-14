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

int	ft_free_token(t_tree *t)
{
	if (t && t != NULL)
		free(t);
	return (-1);
}

int	ft_free_tree(t_tree *c)
{
	t_tree *r;
	t_tree *tmp;

	if (!c)
		return (0);
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

int	ft_free_array(char **argv)
{
	int		i;
	char	*t;

	i = 0;
	while (argv && argv[i])
	{
		t = argv[i++];
		free(t);
	}
	if (argv)
		free(argv);
	return (0);
}

int	ft_free_process(t_process *p)
{
	ft_free_array(p->argv);
	free(p);
	return (0);
}
