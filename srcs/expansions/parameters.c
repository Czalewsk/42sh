/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:59:37 by thugo             #+#    #+#             */
/*   Updated: 2018/01/27 18:38:58 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_sh.h"

t_list	*expand_parameters(t_token *tk)
{
	t_list	*lst[2];
	t_token	newtk;
	char	**splitval;
	char	*val[2];
	int		i;

	lst[0] = NULL;
	if (tk->id != PARAM_EXP || !(val[0] = ft_getenv(g_sh.env, tk->str + 1)))
		return (NULL);
	val[1] = ft_getenv(g_sh.env, "IFS");
	if (!(splitval = ft_strsplits(val[0], val[1] ? val[1] : " \t\n")))
		return (NULL);
	i = -1;
	newtk.id = WORD;
	while (splitval[++i])
	{
		newtk.str = splitval[i];
		newtk.size = ft_strlen(newtk.str);
		if (!(lst[1] = ft_lstnew(&newtk, sizeof(t_token))))
			exit(EXIT_FAILURE);
		ft_lst_pushend(&lst[0], lst[1]);
	}
	free(splitval);
	return (lst[0]);
}
