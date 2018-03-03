/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_tilde_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 02:08:47 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 03:32:47 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define TOKENS {"\\~", "'~'", "\"~\"", NULL}

int		expansions_tilde_escape(void)
{
	int		i;
	t_list	*lst;
	t_token	tk;
	char	ret;
	char	*tokens[] = TOKENS;

	g_sh.env = utils_venvinit();
	i = -1;
	while (tokens[++i])
	{
		tk.str = strdup(tokens[i]);
		tk.size = strlen(tk.str);
		tk.id = WORD;
		ret = expansions_expand(&lst, &tk);
		free(tk.str);
		if (ret || lst)
			return (expansions_utils_free(&g_sh.env, &lst, -1));
		expansions_utils_free(NULL, &lst, 0);
	}
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}
