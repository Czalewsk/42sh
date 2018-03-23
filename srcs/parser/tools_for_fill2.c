/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:04:55 by maastie           #+#    #+#             */
/*   Updated: 2018/03/20 16:04:55 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree			*cpy_from_tree(t_tree *c)
{
	t_tree		*new;
	t_tree		*save;

	new = NULL;
	while (c)
	{
		if (!new)
		{
			new = (t_tree *)ft_memalloc(sizeof(t_tree));
			new->token.str = ft_strdup(c->token.str);
			new->token.id = c->token.id;
			new->token.size = c->token.size;
			save = new;
		}
		else
		{
			new->right = (t_tree *)ft_memalloc(sizeof(t_tree));
			new->right->token.str = ft_strdup(c->token.str);
			new->right->token.id = c->token.id;
			new->right->token.size = c->token.size;
			new = new->right;
		}
		c = c->right;
	}
	return (save);
}

void			closeinouterr(t_process *p)
{
	if (p->closein == 1)
		close(STDIN_FILENO);
	if (p->closeout == 1)
		close(STDOUT_FILENO);
	if (p->closeerr == 1)
		close(STDERR_FILENO);
}

void			closeall(int pipe[2][2])
{
	close(pipe[0][0]);
	close(pipe[0][1]);
	close(pipe[1][0]);
	close(pipe[1][1]);
}

void			dernier_premier(t_process *p)
{
	if (p->stdin != STDIN_FILENO)
		dup2(p->stdin, STDIN_FILENO);
	if (p->stdout != STDOUT_FILENO)
		dup2(p->stdout, STDOUT_FILENO);
	if (p->stderr != STDERR_FILENO)
		dup2(p->stderr, STDERR_FILENO);
}

void			modify_io_child(t_process *p, int pipe[2][2], int pr, int dr)
{
	closeinouterr(p);
	if (dr && pr)
		dernier_premier(p);
	if (!dr)
	{
		if (p->stdout != STDOUT_FILENO)
			dup2(p->stdout, STDOUT_FILENO);
		else
			dup2(pipe[1][1], STDOUT_FILENO);
		if (p->stdin != STDIN_FILENO)
			dup2(p->stdin, STDIN_FILENO);
	}
	if (!pr)
	{
		if (p->stdin != STDIN_FILENO)
			dup2(p->stdin, STDIN_FILENO);
		else
			dup2(pipe[1][0], STDIN_FILENO);
		if (p->stdout != STDOUT_FILENO)
			dup2(p->stdout, STDOUT_FILENO);
	}
	closeall(pipe);
}
