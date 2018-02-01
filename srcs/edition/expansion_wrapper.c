/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wrapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 23:52:47 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/01 13:59:21 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	get_address_end(t_list ***tmp)
{
	if (!**tmp)
		return ;
	while (**tmp)
		*tmp = &(**tmp)->next;
	return ;
}

char		get_globbing(char *tkkn, t_list **res)
{
	t_list	*tmp;
	t_list	*final;
	t_list	*glob;
	t_list	**to_add;

	if (!*res)
		return (sh_glob(tkkn, res));
	final = NULL;
	to_add = &final;
	tmp = *res;
	while (tmp)
	{
		get_address_end(&to_add);
		if (sh_glob(tmp->content, &glob))
			*to_add = glob;
		else
			*to_add = ft_lstnew_str(tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
	}
	ft_lstdel(res, NULL);
	*res = final;
	return (1);
}

char		*expansion_get_word(t_buf *cmd, t_read *info)
{
	char	*start;
	char	*end;
	char	*cursor;
	char	*tmp;

	cursor = cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char, 1);
	tmp = cmd->cmd;
	start = tmp;
	end = tmp;
	while (*tmp++)
	{
		if (tmp >= cursor && (*tmp == ' ' || !*tmp))
		{
			end = tmp;
			break ;
		}
		else if (*tmp == ' ' && tmp <= cursor)
		{
			start = tmp + 1;
			end = start;
		}
	}
	g_sh->comp_start = start;
	g_sh->comp->end = end;
	return (ft_strsub(start, 0, end - start));
}

char	expansion_wrapper(t_buf *cmd, t_read *info, t_key *entry)
{
	char		auto_completion;
	t_list		*res;
	char		*tkkn;

	auto_completion = 1;
	tkkn = expansion_get_word(cmd, info);
	if (sh_brace_exp(tkkn, &res))
		auto_completion = 0;
	if (get_globbing(tkkn, &res))
		auto_completion = 0;
	if (auto_completion)
	{
		(void)entry; // Pour lautocompletion
		ft_strdel(&tkkn);
		DEBUG("AUTO_COMPLETION\n");
	}
	else
		expansion_replace(cmd, info, res);
	/* DEBUG */
	t_list	*tmp;
	if (res)
	{
		tmp = res;
		while (tmp)
		{
			DEBUG("%s|\n", tmp->content);
			tmp = tmp->next;
		}
	}
	/* TEST */
	return (0);
}
