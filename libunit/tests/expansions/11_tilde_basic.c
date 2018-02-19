/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_tilde_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:47:57 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 05:28:06 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN_VALUE "~"
#define $_HOME "/Users/tim"

int		expansions_tilde_basic(void)
{
	t_list	*lst;
	t_token	tk;
	t_token	*newtk;
	char	ret;

	g_sh.env = utils_venvinit();
	utils_venvadd(&g_sh.env, "HOME", $_HOME);
	tk.str = strdup(TOKEN_VALUE);
	tk.size = strlen(tk.str);
	tk.id = WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	if (!ret || !lst)
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	newtk = (t_token *)lst->content;
	if (strcmp(newtk->str, $_HOME) || newtk->size != strlen($_HOME))
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}
