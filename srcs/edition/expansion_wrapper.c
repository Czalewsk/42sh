/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wrapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 23:52:47 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/03 12:24:59 by czalewsk         ###   ########.fr       */
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
			*to_add = ft_lstnew(tmp->content, ft_strlen(tmp->content) + 1);
		tmp = tmp->next;
	}
	ft_lstdel(res, &ft_lst_del_str);
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
	g_sh.comp_start = start;
	g_sh.comp_end = end;
	return (ft_strsub(start, 0, end - start));
}

void		expansion_replace(t_buf *cmd, t_read *info, t_list *res)
{
	size_t		len_replace;
	char		*new_cmd;
	t_list		*tmp;
	char		*curs;

	tmp = res;
	len_replace = 0;
	while (tmp)
	{
		len_replace += (ft_strlen(tmp->content) + 1);
		tmp = tmp->next;
	}
	new_cmd = ft_strnew(ft_strlen(cmd->cmd) - (g_sh.comp_end - g_sh.comp_start)
			+ len_replace);
	curs = ft_strncat(new_cmd, cmd->cmd, g_sh.comp_start - cmd->cmd);
	tmp = res;
	while (tmp)
	{
		curs = ft_strcat(curs, tmp->content);
		curs = ft_strcat(curs, " ");
		tmp = tmp->next;
	}
	ft_strcat(curs, g_sh.comp_end);
	display_str(cmd, info, new_cmd, (g_sh.comp_start - cmd->cmd) + len_replace);
	free(new_cmd);
}

char		expansion_wrapper(t_buf *cmd, t_read *info, t_key *entry)
{
	char		auto_completion;
	t_list		*res;
	char		*tkkn;

	auto_completion = 1;
	tkkn = expansion_get_word(cmd, info);
	DEBUG("tkkn=%s|\n", tkkn);
	if (sh_brace_exp(tkkn, &res))
		auto_completion = 0;
	if (get_globbing(tkkn, &res))
		auto_completion = 0;
	if (auto_completion)
	{
		(void)entry; // Pour lautocompletion attention tkkn est free a la fin
		DEBUG("AUTO_COMPLETION\n");
	}
	else
	{
		expansion_replace(cmd, info, res);
		ft_lstdel(&res, ft_lst_del_str);
	}
	ft_strdel(&tkkn);
	return (0);
}
