/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 06:48:15 by thugo             #+#    #+#             */
/*   Updated: 2018/03/10 16:32:02 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static t_expands_rules	g_expands[] = {
	{expand_tilde, 2, {WORD, ASSIGNMENT_WORD}},
	{expand_parameters, 2, {WORD, ASSIGNMENT_WORD}},
	{expand_globing, 1, {WORD}},
	{expand_history_expoint, 1, {HISTORY_EXPOINT}},
	{NULL, 0, {0}},
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
**
**	Retourne:
**		1: Si une expansion a ete realise (Utiliser le contenu de la liste. Si
**			liste est NULL, supprimer le token).
**		0: Si aucune expansion a ete realise. (Utiliser le token original)
*/

char	expansions_expand(t_list **lst, const t_token *tk)
{
	int		i;
	int		u;

	i = -1;
	*lst = NULL;
	while (g_expands[++i].fn)
	{
		u = -1;
		while (++u < g_expands[i].sizeallowed)
			if (g_expands[i].allowed[u] == tk->id)
				if (g_expands[i].fn(tk, lst))
					return (1);
	}
	return (0);
}
