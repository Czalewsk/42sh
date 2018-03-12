/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 21:03:58 by maastie           #+#    #+#             */
/*   Updated: 2018/02/24 21:03:59 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			read_hr(char *hr, char *ref)
{
	if (ft_strlen(hr) - 1 == 0)
		return (-1);
	else if (ft_memcmp(hr, ref, ft_strlen(hr) - 1) != 0)
		return (-1);
	return (0);
}

t_tree		*here_doc(t_process *p, t_tree *c)
{
	int		*fd;

	fd = here_list->content;
	close(STDIN_FILENO);
	close(fd[1]);
	p->stdin = dup(fd[0]);
	close(fd[0]);
	c = c->right->right;
	while (c && c->token.id == DLESS)
		c = c->right->right;
	ft_lst_remove_index(&here_list, 0, NULL);
	return (c);
}

t_tree	*add_new_fd(t_tree *new)
{
	int		fd[2];
	char	*hr;

	if (!here_list)
		here_list = NULL;
	if (pipe(fd) == -1)
		return ((void *)1);
	hr = NULL;
	while (prompt_add("> ", &hr, 1) == -2)
	{
		if (read_hr(hr, new->token.str) == 0)
			break ;
		ft_putstr_fd(hr, fd[1]);
		ft_strdel(&hr);		
	}
	// while (read_hr(hr, new->token.str) != 0) // check sur e ctrl c // d
	// {
	// 	ft_putstr_fd(hr, fd[1]);
	// 	ft_strdel(&hr);
	// 	if (prompt_add("> ", &hr, 1) != -2)
	// 		break ;
	// 	prompt_add("> ", &hr, 1);
	// }
	ft_strdel(&hr);
	ft_lst_pushend(&here_list, ft_lstnew(&fd, sizeof(int *)));
	return (new);
}

t_tree	*add_current_fd(t_tree *new)
{
	char	*hr;
	int		*fd;

	fd = here_list->content;
	prompt_add("> ", &hr, 1);
	while (read_hr(hr, new->token.str) != 0) // check sur e ctrl c // d
	{
		ft_putstr_fd(hr, fd[1]);
		ft_strdel(&hr);
		if (prompt_add("> ", &hr, 1) != -2)
			break ;
	}
	ft_strdel(&hr);
	return (new);
}

t_tree	*here(t_tree *current, t_tree *new)
{
	t_tree	*tmp;

	tmp = current;
	while (tmp)
	{
		tmp = tmp->previous;
		if (tmp && tmp->token.id == DLESS)
			return (add_current_fd(new));
	}
	return (add_new_fd(new));
}