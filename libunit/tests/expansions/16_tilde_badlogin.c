/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_tilde_badlogin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 05:37:12 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 05:37:41 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN "~badlogin"

int		expansions_tilde_badlogin(void)
{
	t_list	*lst;
	t_token	tk;
	char	ret;

	g_sh.env = utils_venvinit();
	tk.str = strdup(TOKEN);
	tk.size = strlen(tk.str);
	tk.id = WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	if (ret || lst)
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}
