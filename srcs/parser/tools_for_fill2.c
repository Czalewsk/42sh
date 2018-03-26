/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:04:55 by maastie           #+#    #+#             */
/*   Updated: 2018/03/26 19:55:38 by czalewsk         ###   ########.fr       */
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

void			modify_io_child(t_process *p)
{
	t_list		*tmp;
	t_fd		*test_fd;

	tmp = p->fd_list;
	while (tmp)
	{
		test_fd = tmp->content;
//		DEBUG("left=%d str=[%s]|\n\n right = %d str=[%s]|\n\n\n", test_fd->left_fd,test_fd->left_str, test_fd->right_fd, test_fd->right_str);
		test_fd->fd_action(test_fd->left_str, test_fd->right_str, test_fd->io_default); // gerer erreur dup2
		tmp = tmp->next;
	}
}

void			do_pipe_child(int pipe[2][2], int pr, int dr)
{
	if (!dr)
			dup2(pipe[1][1], STDOUT_FILENO);
	if (!pr)
			dup2(pipe[1][0], STDIN_FILENO);
	close(pipe[0][0]);
	close(pipe[0][1]);
	close(pipe[1][0]);
	close(pipe[1][1]);
}
