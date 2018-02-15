/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:24:14 by thugo             #+#    #+#             */
/*   Updated: 2018/02/13 15:14:55 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static t_expands_rules	g_expands[] = {
	{expand_parameters, 2, {WORD, ASSIGNMENT_WORD}},
	{NULL, 0, {}},
};

void	expansions_addtoken(t_list **lst, char *str, t_token_id id)
{
	t_token		tk;

	if (!str)
		return ;
	tk.str = str;
	tk.size = ft_strlen(str);
	tk.id = id;
	ft_lst_pushend(lst, ft_lstnew(&tk, sizeof(t_token)));
}

/*
**	Realise l'expansion de chaque token.
**	Retourne:
**		Une liste de token si expansion faite, sinon NULL.
*/

t_list	*expansions_expand(t_token *tk)
{
	int		i;
	int		u;
	t_list	*lst;

	i = -1;
	lst = NULL;
	while (g_expands[++i].fn && !lst)
	{
		u = -1;
		while (++u < g_expands[i].sizeallowed)
			if (g_expands[i].allowed[u] == tk->id)
				g_expands[i].fn(tk, &lst);
	}
	return (lst);
}
