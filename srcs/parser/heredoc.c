/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 21:03:58 by maastie           #+#    #+#             */
/*   Updated: 2018/03/28 21:48:42 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		*signal_leav_here_doc(void)
{
	while (g_here_list)
		remove_here_list();
	return ((void *)1);
}

t_tree		*add_new_fd(t_tree *new, t_here *here, int number)
{
	char			*hr;
	int				ret_p;
	char			*ref;

	ref = ft_strjoin(new->token.str, "\n");
	if (!g_here_list)
		g_here_list = NULL;
	if (pipe(here->fd) == -1)
		return ((void *)1);
	hr = NULL;
	here->num = number;
	while ((ret_p = prompt_add("> ", &hr, 1)) == -2)
	{
		if (ret_p == -1 || ft_strequ(hr, ref) == 1)
			break ;
		ft_putstr_fd(hr, here->fd[1]);
		ft_strdel(&hr);
	}
	ft_strdel(&ref);
	ft_strdel(&hr);
	if (ret_p == -3)
		return (signal_leav_here_doc());
	ft_lst_pushend(&g_here_list, ft_lstnew(here, sizeof(t_here)));
	return (new);
}

t_tree		*here(t_tree *current, t_tree *new)
{
	t_tree		*tmp;
	t_here		new_h;
	static int	here_num;

	tmp = current;
	if (g_sh.subshellactive == 1)
	{
		sh_error(-1, 0, NULL, 1,
			"Error, here-doc not supported on substitute command\n");
		return ((void *)1);
	}
	ft_bzero(&new_h, sizeof(t_here));
	while (tmp)
	{
		tmp = tmp->previous;
		if (tmp && (tmp->token.id == OR_IF
			|| tmp->token.id == AND_IF))
			break ;
		if (tmp && tmp->token.id == DLESS)
			return (add_new_fd(new, &new_h, here_num));
	}
	return (add_new_fd(new, &new_h, ++here_num));
}

void		sh_heredoc_remove(t_here *content)
{
	close(content->fd[0]);
	close(content->fd[1]);
	free(content);
}
