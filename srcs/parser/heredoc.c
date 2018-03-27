/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 21:03:58 by maastie           #+#    #+#             */
/*   Updated: 2018/03/27 11:46:29 by czalewsk         ###   ########.fr       */
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

t_tree		*add_new_fd(t_tree *new, t_here *here, int number)
{
	char			*hr;
	int				ret_p;

	if (!g_here_list)
		g_here_list = NULL;
	if (pipe(here->fd) == -1)
		return ((void *)1);
	hr = NULL;
	here->num = number;
	while ((ret_p = prompt_add("> ", &hr, 1)) == -2)
	{
		if (ret_p == -1 || read_hr(hr, new->token.str) == 0)
			break ;
		ft_putstr_fd(hr, here->fd[1]);
		ft_strdel(&hr);
	}
	ft_strdel(&hr);
	if (ret_p == -3)
		return ((void *)1);
	ft_lst_pushend(&g_here_list, ft_lstnew(here, sizeof(t_here)));
	return (new);
}

t_tree		*add_current_fd(t_tree *new, t_here *here, int number)
{
	char	*hr;
	int		ret_p;
	t_list	*tmp;
	t_here	*tmph;

	tmp = g_here_list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmph = tmp->content;
	here->fd[0] = tmph->fd[0];
	here->fd[1] = tmph->fd[1];
	here->num = number;
	while ((ret_p = prompt_add("> ", &hr, 1)) == -2)
	{
		if (ret_p == -1 || read_hr(hr, new->token.str) == 0)
			break ;
		ft_putstr_fd(hr, here->fd[1]);
		ft_strdel(&hr);
	}
	ft_strdel(&hr);
	if (ret_p == -3)
		return ((void *)1);
	ft_lst_pushend(&g_here_list, ft_lstnew(here, sizeof(t_here)));
	return (new);
}

t_tree		*here(t_tree *current, t_tree *new)
{
	t_tree		*tmp;
	t_here		*new_h;
	static int	here_num;

	tmp = current;
	new_h = (t_here *)ft_memalloc(sizeof(t_here));
	while (tmp)
	{
		tmp = tmp->previous;
		if (tmp && (tmp->token.id == PIPE
			|| tmp->token.id == AND_IF
			|| tmp->token.id == OR_IF))
		{
			break ;
		}
		if (tmp && tmp->token.id == DLESS)
			return (add_current_fd(new, new_h, here_num));
	}
	return (add_new_fd(new, new_h, ++here_num));
}
