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

void		*get_fonction_from_token(t_tree *c)
{
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
	t_fd	new;

	ft_bzero(&new, sizeof(t_fd));
	if (c->previous && c->previous->token.id != IO_NUMBER)
		new.io_default = 1;
	new.right_str = ft_strdup(c->right->token.str);
	new.fd_action = get_fonction_from_token(c);
	ft_lst_pushend(&p->fd_list, ft_lstnew(&new, sizeof(t_fd)));
	return (c->right->right);
}

t_tree		*modify_io(t_process *p, t_tree *c)
{
	t_list	*last_fd;
	t_fd	*n_fd;

	if (c->right->token.id == DLESS
		&& (add_heredoc_in_process(p, c->right) || 1))
		return (c->right->right->right);
	set_fd_in_process(p, c->right);
	last_fd = p->fd_list;
	while (last_fd->next)
		last_fd = last_fd->next;
	n_fd = last_fd->content;
	n_fd->left_str = ft_strdup(c->token.str);
	return (c->right->right->right);
}

void		remove_here_list(void)
{
	t_list	*tmp_list;
	t_here	*tmph;
	int		ref_here;

	tmp_list = g_here_list;
	tmph = tmp_list->content;
	ref_here = tmph->num;
	while (tmp_list)
	{
		tmph = tmp_list->content;
		tmp_list = tmp_list->next;
		if (tmph->num != ref_here)
			break ;
		close(tmph->fd[0]);
		close(tmph->fd[1]);
		ft_lst_remove_index(&g_here_list, 0, NULL);
	}
}

t_tree		*add_heredoc_in_process(t_process *p, t_tree *c)
{
	t_fd	new;

	ft_bzero(&new, sizeof(t_fd));
	if (c->previous && c->previous->token.id == IO_NUMBER)
		new.left_str = ft_strdup(c->previous->token.str);
	else
		new.io_default = 1;
	new.here_doc = ((t_here*)g_here_list->content)->fd[0];
	new.fd_action = get_fonction_from_token(c);
	ft_lst_pushend(&p->fd_list, ft_lstnew(&new, sizeof(t_fd)));
	ft_lstadd(&p->open_fd,
		ft_lstnew(((t_here*)g_here_list->content)->fd, sizeof(int)), 0);
	close(((t_here*)g_here_list->content)->fd[1]);
	ft_lst_remove_index(&g_here_list, 0, NULL);
	return (c->right->right);
}
