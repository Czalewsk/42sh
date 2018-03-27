/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:31:14 by maastie           #+#    #+#             */
/*   Updated: 2018/03/27 15:15:51 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/*
	Si le new->right/left == -2 ferme le fd
	Si le new->right/left == -1 erreur

	// sur les &> le left est un argument;
*/


void	*get_fonction_from_token(t_tree *c)
{
	DEBUG("\tc_str=[%s]|\n", c->token.str);
	if (c->token.id == GREAT)
		return (sh_great);
	if (c->token.id == GREATAND)
		return (sh_greatand);
	if (c->token.id == LESSAND)
		return (sh_lessand);
	if (c->token.id == LESS)
		return (sh_less);
	if (c->token.id == LESSGREAT)
		return (sh_lessgreat);
	if (c->token.id == DGREAT)
		return (sh_dgreat);
	if (c->token.id == DLESS)
		return (sh_dless);
	return (NULL);
}

t_tree		*set_fd_in_process(t_process *p, t_tree *c)
{
	t_fd	*new;

	new = (t_fd *)ft_memalloc(sizeof(t_fd));
	if (c->previous && c->previous->token.id != IO_NUMBER)
		new->io_default = 1;
	new->right_str = ft_strdup(c->right->token.str);
	new->fd_action = get_fonction_from_token(c);
	ft_lst_pushend(&p->fd_list, ft_lstnew(new, sizeof(t_fd)));
	return (c->right->right);
}

t_tree		*modify_io(t_process *p, t_tree *c)
{
	t_list		*last_fd;
	t_fd		*n_fd;

	set_fd_in_process(p, c->right);
	last_fd = p->fd_list;
	while (last_fd->next)
		last_fd = last_fd->next;
	n_fd = last_fd->content;
	n_fd->left_str = ft_strdup(c->token.str);
	return (c->right->right->right);
}

t_tree		*add_heredoc_in_process(t_process *p, t_tree *c)
{
	t_fd	*new;

	new = (t_fd *)ft_memalloc(sizeof(t_fd));
	if (c->previous && c->previous->token.id == IO_NUMBER)
		new->left_str = ft_strdup(c->token.str);
	else
		new->io_default = 1;
	new->fd_action = get_fonction_from_token(c);
	ft_lst_pushend(&p->fd_list, ft_lstnew(new, sizeof(t_fd)));
	ft_lst_pushend(&p->open_fd, ft_lstnew(((t_here*)g_here_list->content)->fd, sizeof(int)));
	ft_lst_pushend(&p->open_fd, ft_lstnew(((t_here*)g_here_list->content)->fd + 1, sizeof(int)));
	return (c->right->right);
}
