/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:24:14 by thugo             #+#    #+#             */
/*   Updated: 2018/01/27 16:27:24 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static t_list	*(*g_expands[])(t_token *) = {
	expand_parameters,
	NULL
};

/*
**	Realise l'expansion de chaque token.
**	Retourne:
**		Une liste de token si expansion faite, sinon NULL.
*/

t_list	*expansions_expand(t_token *tk)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while (g_expands[i] && !(lst = g_expands[i](tk)))
		++i;
	return (lst);
}
