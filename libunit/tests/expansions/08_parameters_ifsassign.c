/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_parameters_ifsassign.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:46:03 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 20:57:24 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "ft_sh.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN_VALUE "mavar=$arg1$arg2.cc$arg1.cc$arg2.cc"
#define IFS " \t"
#define ARG1_VALUE "ls \t  \t -la"
#define ARG2_VALUE "\t   ls\t-la       "
#define FULL_STR "mavar=" ARG1_VALUE ARG2_VALUE ".cc" ARG1_VALUE ".cc" \
	ARG2_VALUE ".cc"

extern t_sh	g_sh;

int		expansions_parameters_ifsassign(void)
{
	t_list	*lst;
	t_token	tk;
	t_token	*newtk;
	char	ret;

	g_sh.env = utils_venvinit();
	utils_venvadd(&g_sh.env, "IFS", IFS);
	utils_venvadd(&g_sh.env, "arg1", ARG1_VALUE);
	utils_venvadd(&g_sh.env, "arg2", ARG2_VALUE);
	tk.str = strdup(TOKEN_VALUE);
	tk.size = strlen(tk.str);
	tk.id = ASSIGNMENT_WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	utils_venvdestroy(g_sh.env);
	if (!ret || !lst || lst->next)
		return (expansions_utils_freelst(lst, -1));
	newtk = (t_token*)lst->content;
	if (strcmp(newtk->str, FULL_STR) || newtk->size != strlen(FULL_STR))
		return (expansions_utils_freelst(lst, -1));
	return (expansions_utils_freelst(lst, 0));
}
