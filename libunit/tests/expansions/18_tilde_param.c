/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_tilde_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 06:44:51 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 06:53:23 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define $_HOME "/Users/tim"
#define $_ARG1 "plop"
#define $_ARG2 "~"

#define TOKENS {"~$ARG1", "~$ARG2", "$ARG2", NULL}
#define TOKENS_VALID_STR {"~plop", "~~", "~"}
#define TOKENS_VALID_RET {1, 1, 1}

int		expansions_tilde_param(void)
{
	int		i;
	t_list	*lst;
	t_token	tk;
	t_token	*newtk;
	char	ret;
	char	*tokens[] = TOKENS;
	char	*tokens_valid_str[] = TOKENS_VALID_STR;
	char	tokens_valid_ret[] = TOKENS_VALID_RET;

	g_sh.env = utils_venvinit();
	utils_venvadd(&g_sh.env, "HOME", $_HOME);
	utils_venvadd(&g_sh.env, "ARG1", $_ARG1);
	utils_venvadd(&g_sh.env, "ARG2", $_ARG2);
	i = -1;
	while (tokens[++i])
	{
		tk.str = strdup(tokens[i]);
		tk.size = strlen(tk.str);
		tk.id = WORD;
		ret = expansions_expand(&lst, &tk);
		free(tk.str);
		if (ret != tokens_valid_ret[i] || (!tokens_valid_ret[i] && lst))
			return (expansions_utils_free(&g_sh.env, &lst, -1));
		if (tokens_valid_ret[i])
		{
			newtk = (t_token *)lst->content;
			if (strcmp(newtk->str, tokens_valid_str[i]) || newtk->size !=
					strlen(tokens_valid_str[i]))
				return (expansions_utils_free(&g_sh.env, &lst, -1));
		}
		expansions_utils_free(NULL, &lst, 0);
	}
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}