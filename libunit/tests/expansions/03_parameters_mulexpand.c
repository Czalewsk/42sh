/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parameters_mulexpand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:46:00 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 02:58:04 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN_VALUE "$arg1$arg2$arg3"
#define ARG1_VALUE "coucou_"
#define ARG2_VALUE "$camarche_bien?"
#define ARG3_VALUE ""
#define FULL_STR ARG1_VALUE ARG2_VALUE ARG3_VALUE

int		expansions_parameters_mulexpand(void)
{
	t_list	*lst;
	t_token	tk;
	t_token	*newtk;
	char	ret;

	g_sh.env = utils_venvinit();
	utils_venvadd(&g_sh.env, "arg1", ARG1_VALUE);
	utils_venvadd(&g_sh.env, "arg2", ARG2_VALUE);
	utils_venvadd(&g_sh.env, "arg3", ARG3_VALUE);
	tk.str = strdup(TOKEN_VALUE);
	tk.size = strlen(tk.str);
	tk.id = WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	if (!ret || !lst || lst->next)
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	newtk = (t_token*)lst->content;
	if (strcmp(newtk->str, FULL_STR) || newtk->size != strlen(FULL_STR))
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}
