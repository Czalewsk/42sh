/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_tilde_slash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 05:39:51 by thugo             #+#    #+#             */
/*   Updated: 2018/02/23 01:17:32 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libunit_utils.h"
#include "expansions.h"
#include "expansions_utils.h"

#define $_HOME "/Users/tim"

#define TOKENS {"~/", "/~", "~/coucou/plop", "~///////",  NULL}
#define TOKENS_VALID_STR {$_HOME"/", NULL, $_HOME"/coucou/plop", $_HOME"///////"}
#define TOKENS_VALID_RET {1, 0, 1, 1, 1}

int		expansions_tilde_slash(void)
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
			if (!lst)
				return (expansions_utils_free(&g_sh.env, &lst, -1));
			newtk = (t_token *)lst->content;
			if (strcmp(newtk->str, tokens_valid_str[i]) || newtk->size !=
					strlen(tokens_valid_str[i]))
				return (expansions_utils_free(&g_sh.env, &lst, -1));
		}
		expansions_utils_free(NULL, &lst, 0);
	}
	return (expansions_utils_free(&g_sh.env, &lst, 0));
}
