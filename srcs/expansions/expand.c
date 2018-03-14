/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 06:48:15 by thugo             #+#    #+#             */
/*   Updated: 2018/03/13 22:42:58 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static t_expands_rules	g_expands[] = {
	{expand_history_expoint, 1, {HISTORY_EXPOINT}, 0},
	{expand_tilde, 2, {WORD, ASSIGNMENT_WORD}, 0},
	{expand_parameters, 2, {WORD, ASSIGNMENT_WORD}, 0},
	{expand_globing, 1, {WORD}, 1},
	{NULL, 0, {0}, 0},
};

void		expansions_addtoken(t_list **lst, char *str, t_token_id id)
{
	t_token		tk;

	if (!str)
		return ;
	tk.str = str;
	tk.size = ft_strlen(str);
	tk.id = id;
	ft_lst_pushend(lst, ft_lstnew(&tk, sizeof(t_token)));
}

static void	add_new_lst(t_list **lst, t_list **cur, t_list **prev, t_list *new)
{
	if (!*prev)
		*lst = new;
	else
		(*prev)->next = new;
	*prev = new;
	while ((*prev)->next)
		*prev = (*prev)->next;
	ft_lst_pushend(&new, (*cur)->next);
	free(((t_token *)(*cur)->content)->str);
	free((*cur)->content);
	free(*cur);
	*cur = *prev;
}

static char	expand_lst(t_list **lst, int i)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*new;
	int		ret;

	ret = 0;
	cur = *lst;
	prev = NULL;
	while (cur)
	{
		new = NULL;
		if (g_expands[i].fn((t_token *)cur->content, &new) && new)
		{
			add_new_lst(lst, &cur, &prev, new);
			ret = 1;
		}
		prev = cur;
		cur = cur->next;
	}
	return (ret);
}

static int	expand_token(t_list **lst, const t_token *tk, int i)
{
	int		u;

	u = -1;
	while (++u < g_expands[i].sizeallowed)
		if (g_expands[i].allowed[u] == tk->id)
			return (g_expands[i].fn(tk, lst));
	return (0);
}

/*
**	Realise l'expansion de chaque token.
**
**	Retourne:
**		 1: Si une expansion a ete realise (Utiliser le contenu de la liste. Si
**			liste est NULL, supprimer le token).
**		 0: Si aucune expansion a ete realise. (Utiliser le token original)
**		-1: Si une erreur est survenue. Il faut quitter l'execution.
*/

char		expansions_expand(t_list **lst, const t_token *tk)
{
	int		i;
	int		ret;
	int		exp;

	i = -1;
	*lst = NULL;
	exp = 0;
	while (g_expands[++i].fn)
	{
		if (*lst && expand_lst(lst, i) && g_expands[i].break_on_exp)
			return (1);
		else if (!*lst)
		{
			if ((ret = expand_token(lst, tk, i)) == 1)
				exp = 1;
			else if (ret == -1)
				return (-1);
		}
	}
	return (exp);
}
