/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:59:59 by thugo             #+#    #+#             */
/*   Updated: 2018/03/19 13:51:48 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "utils.h"

static t_list	*get_globing(char *str)
{
	t_list	*lst;
	t_list	*cur;
	t_list	*prev;

	lst = NULL;
	if (sh_globbing(str, &cur))
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

char			expand_globing(const t_token *tk, t_list **lst)
{
	if (tk && (*lst = get_globing(tk->str)))
		return (1);
	return (0);
}
