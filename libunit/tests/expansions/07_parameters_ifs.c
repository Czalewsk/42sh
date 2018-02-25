/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_parameters_ifs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:54:11 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 02:59:10 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN_VALUE "coucou$arg1.coucou$arg2.encore"
#define IFS "ou"
#define ARG1_VALUE "lsouuou-la"
#define ARG2_VALUE "ouuoouuoolsouuouou-laouuoouu"
#define VALID_RETURN {"coucouls", "-la.coucou", "ls", "-la", ".encore", NULL}

int		expansions_parameters_ifs(void)
{
	t_list	*lst;
	t_list	*cur;
	t_token	tk;
	t_token	*newtk;
	char	ret;
	char	*valid_return[] = VALID_RETURN;
	int		i;

	g_sh.env = utils_venvinit();
	utils_venvadd(&g_sh.env, "IFS", IFS);
	utils_venvadd(&g_sh.env, "arg1", ARG1_VALUE);
	utils_venvadd(&g_sh.env, "arg2", ARG2_VALUE);
	tk.str = strdup(TOKEN_VALUE);
	tk.size = strlen(tk.str);
	tk.id = WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	if (!ret || !lst)
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	cur = lst;
	i = 0;
	while (cur && valid_return[i])
	{
		newtk = (t_token*)cur->content;
		if (strcmp(newtk->str, valid_return[i]) || newtk->size !=
				strlen(valid_return[i]))
			return (expansions_utils_free(&g_sh.env, &lst, -1));
		cur = cur->next;
		++i;
	}
	if (cur || valid_return[i])
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}
