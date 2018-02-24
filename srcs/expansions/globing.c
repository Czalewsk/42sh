/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:59:59 by thugo             #+#    #+#             */
/*   Updated: 2018/02/24 16:08:16 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh_glob.h"

static t_list	*get_globing(char *str)
{
	t_list	*lst;
	t_list	*cur;
	t_list	*prev;

	lst = NULL;
	if (sh_glob(str, &cur))
	{
		while (cur)
		{
			expansions_addtoken(&lst, (char *)cur->content, WORD);
			prev = cur;
			cur = cur->next;
			free(prev);
		}
	}
	return (lst);
}

static void		glob_parameters(t_list **lst)
{
	t_list	*cur;
	t_list	*new;
	t_list	*prev;

	prev = NULL;
	cur = *lst;
	while (cur)
	{
		if ((new = get_globing((char *)(((t_token *)(cur->content))->str))))
		{
			if (!prev)
				*lst = new;
			else
				prev->next = new;
			ft_lst_pushend(&new, cur->next);
			free(((t_token *)(cur->content))->str);
			free(cur->content);
			free(cur);
			cur = new;
		}
		prev = cur;
		cur = cur->next;
	}
}

char			expand_globing(const t_token *tk, t_list **lst)
{
	if (tk && (*lst = get_globing(tk->str)))
		return (1);
	if (!tk && *lst)
	{
		glob_parameters(lst);
		return (1);
	}
	return (0);
}
