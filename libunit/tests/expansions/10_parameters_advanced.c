/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_parameters_advanced.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 21:06:32 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 02:59:29 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN_VALUE "this$empty_lol\\value$arg1\\$unknow\"$arg2\"c$$$arg3.c$arg4'$cc'"
#define EMPTY_LOL_VALUE ""
#define ARG1_VALUE "va$w  wa l"
#define ARG2_VALUE "1  2  \t 3"
#define ARG3_VALUE "normal$$"
#define ARG4_VALUE " split "
#define VALID_RETURN {"this\\valueva$w", "wa", "l\\$unknow\"1", "2", "3\"c$$normal$$.c", "split", "'$cc'", NULL}

int		expansions_parameters_advanced(void)
{
	t_list	*lst;
	t_list	*cur;
	t_token	tk;
	t_token	*newtk;
	char	ret;
	char	*valid_return[] = VALID_RETURN;
	int		i;

	g_sh.env = utils_venvinit();
	utils_venvadd(&g_sh.env, "arg1", ARG1_VALUE);
	utils_venvadd(&g_sh.env, "arg2", ARG2_VALUE);
	utils_venvadd(&g_sh.env, "arg3", ARG3_VALUE);
	utils_venvadd(&g_sh.env, "arg4", ARG4_VALUE);
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
				strlen(valid_return[i])){
			return (expansions_utils_free(&g_sh.env, &lst, -1));}
		cur = cur->next;
		++i;
	}
	if (cur || valid_return[i])
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}
