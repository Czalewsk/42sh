/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parameters_noexpand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:22:59 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 03:24:29 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "expansions.h"
#include "libunit_utils.h"
#include "expansions_utils.h"

int		expansions_parameters_noexpand(void)
{
	t_list	*lst;
	t_token	tk;
	char	ret;

	g_sh.env = utils_venvinit();
	tk.str = strdup("hel$.owo$$.rld42");
	tk.size = strlen(tk.str);
	tk.id = WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	if (ret || lst)
		return (expansions_utils_free(&g_sh.env, &lst, -1));
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}
