/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:31:14 by maastie           #+#    #+#             */
/*   Updated: 2018/03/19 11:55:05 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/*
	Si le new->right/left == -2 ferme le fd
	Si le new->right/left == -1 erreur

	// sur les >& valid si le fd est open : open (file)
	// sur les &> le left est un argument;
*/

int		open_fd(t_tree *c)
{
	int		ret;

	ret = -1;
	if (c->token.id == LESS)
		ret = open(c->right->token.str, O_RDONLY, 0755);
	else if (c->token.id == GREAT)
		ret = open(c->right->token.str, O_CREAT | O_TRUNC | O_WRONLY, 0755);
	else if (c->token.id == DGREAT)
		ret = open(c->right->token.str, O_APPEND | O_CREAT | O_WRONLY, 0755);
	else if (c->token.id == LESSGREAT)
		ret = open(c->right->token.str, O_RDWR, 0755);
	return (ret);
}

int			get_fd(t_tree *c)
{
	int	ret;

	ret = ft_isint(c->right->token.str) ? ft_atoi(c->right->token.str) : -2;
	if (ret == -2 && ft_memcmp(c->right->token.str, "-", 1) == 0)
		ret = -2;
	// cas du ambigeous redirection
	return (ret);
}

int		init_fd(t_tree *c)
{
	if (c->token.id == GREAT || c->token.id == DGREAT || c->token.id == LESS)
		return (open_fd(c));
	else if (c->token.id == GREATAND || c->token.id == ANDGREAT || c->token.id == LESSAND)
		return (get_fd(c));
	return (-1);
}

t_tree		*set_fd_in_process(t_process *p, t_tree *c)
{
	t_fd	*new;

	new = (t_fd *)ft_memalloc(sizeof(t_fd));
//	DEBUG("|%s|\n", c->right->token.str);
	if (c->token.id == GREATAND || c->token.id == GREAT || c->token.id == DGREAT
		|| c->token.id == ANDGREAT)
		new->left_fd = 1;
	else
		new->left_fd = 0;
///	new->fd_action = get_fonction_from_token(c);
	new->right_fd = init_fd(c);
	ft_lst_pushend(&p->fd_list, ft_lstnew(&new, sizeof(t_fd *)));
	DEBUG("new->left_fd = |%d|, new->right_fd = |%d|\n", new->left_fd, new->right_fd);
	return (c->right->right);
}

int			get_first_fd(t_tree *c)
{
	int		ret;

	ret = -1;
	return (ret);
}

t_tree		*modify_io(t_process *p, t_tree *c)
{
	int			left_fd;
	t_list		*last_fd;
	t_fd		*n_fd;

/*
	left_fd = ft_isint(c->right->token.str) ? ft_atoi(c->right->token.str) : -2;
*/

	set_fd_in_process(p, c->right);
	last_fd = p->fd_list;
	while (last_fd->next)
		last_fd = last_fd->next;
	n_fd = last_fd->content;
	n_fd->left_fd = left_fd;
	return (c->right->right->right);
}
