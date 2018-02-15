/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parameters_basic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:38:39 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 16:32:57 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "ft_sh.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN_VALUE "$arg"
#define ARG_VALUE "hello!"

extern t_sh	g_sh;

int		expansions_parameters_basic(void)
{
	t_list	*lst;
	t_token	tk;
	t_token	*newtk;
	char	ret;

	g_sh.env = utils_venvinit();
	utils_venvadd(&g_sh.env, "arg", ARG_VALUE);
	tk.str = strdup(TOKEN_VALUE);
	tk.size = strlen(tk.str);
	tk.id = WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	utils_venvdestroy(g_sh.env);
	if (!ret || !lst || lst->next)
		return (expansions_utils_freelst(lst, -1));
	newtk = (t_token*)lst->content;
	if (strcmp(newtk->str, ARG_VALUE) || newtk->size != strlen(ARG_VALUE))
		return (expansions_utils_freelst(lst, -1));
	return (expansions_utils_freelst(lst, 0));
}
