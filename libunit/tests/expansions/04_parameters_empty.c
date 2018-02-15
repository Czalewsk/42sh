/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parameters_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 18:57:15 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 19:18:56 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "ft_sh.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKEN_VALUE "$NOTEXIST$NOT"

extern t_sh	g_sh;

int		expansions_parameters_empty(void)
{
	t_list	*lst;
	t_token	tk;
	char	ret;

	g_sh.env = utils_venvinit();
	tk.str = strdup(TOKEN_VALUE);
	tk.size = strlen(tk.str);
	tk.id = WORD;
	ret = expansions_expand(&lst, &tk);
	free(tk.str);
	utils_venvdestroy(g_sh.env);
	if (!ret || lst)
		return (expansions_utils_freelst(lst, -1));
	return (expansions_utils_freelst(lst, 0));
}
