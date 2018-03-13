/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 16:30:15 by thugo             #+#    #+#             */
/*   Updated: 2018/03/13 01:37:54 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void make_tokens(t_list **lst, char *expand)
{
	char	**split;
	int		i;

	split = ft_strsplits(expand, " \t\n");
	i = -1;
	while (split[++i])
		expansions_addtoken(lst, split[i], WORD);
	free(split);
	free(expand);
}

char	expand_history_expoint(const t_token *tk, t_list **lst)
{
	char	*expoint;
	char	*expand;
	char	*start;

	expoint = tk->str;
	while (*expoint && (expoint = ft_strchr(expoint, '!')) &&
			ft_is_escape(expoint, tk->str))
		++expoint;
	if (!expoint)
		return (sh_error(-1, 0, NULL, 2, tk->str, ": event not found\n"));
	if (!(expand = history_expoint(expoint)))
		return (sh_error(-1, 0, NULL, 2, expoint, ": event not found\n"));
	if (expoint == tk->str)
		make_tokens(lst, expand);
	else
	{
		start = ft_strndup(tk->str, expoint - tk->str);
		make_tokens(lst, ft_strjoin_free(start, expand, 2));
	}
	return (1);
}
