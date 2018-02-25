/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_parameters_catexpand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:23:15 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 02:58:41 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN_VALUE "coucou$arg1.itwork$unknow$arg2.lol"
#define ARG1_VALUE "ARG1"
#define ARG2_VALUE "ARG2"
#define FULL_STR "coucou" ARG1_VALUE ".itwork" ARG2_VALUE ".lol"

int		expansions_parameters_catexpand(void)
{
	t_list	*lst;
	t_token	tk;
	t_token	*newtk;
	char	ret;

	g_sh.env = utils_venvinit();
	utils_venvadd(&g_sh.env, "arg1", ARG1_VALUE);
	utils_venvadd(&g_sh.env, "arg2", ARG2_VALUE);
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
