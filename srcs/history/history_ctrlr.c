/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_ctrlr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 15:51:28 by bviala            #+#    #+#             */
/*   Updated: 2018/01/03 18:19:10 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	ft_clear_prompt(t_read *info , int first, size_t pos, char *new)
{
	/*
	if (first)
	{
		cursor_back_home(info);
		ft_putnchar('\b', info->prompt - 1);
	}
	else
		ft_putnchar('\b', 22 + pos + ft_strlen(new));
		*/
	(void)info;
	(void)first;
	(void)pos;
	(void)new;
	tputs(tparm(g_termcaps_cap[COL], 0), 0, &ft_putchar_termcap);
	tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
}

static void	ft_search_prompt(t_read *info, char *to_find, char *new, size_t pos)
{
	ft_clear_prompt(info, 0, pos, new);
	if (to_find)
	{
		ft_printf("(reverse-i-search)`%s': ", to_find);
		if (new)
			ft_putstr(new);
	}
	else
		ft_putstr("(reverse-i-search)`': ");
}

static void	search_history(char **new, char **to_find, size_t *pos, int ret)
{
	char 	tmp[2];
	t_ldl	*ldl;

	ft_clear_prompt(NULL, 0, *pos, *new);
	tmp[0] = (char)ret;
	tmp[1] = '\0';
	++(*pos);
	if (!(*to_find))
		*to_find = ft_strdup(tmp);
	else
		*to_find = ft_strjoin_free(*to_find, tmp, 0);
	if (!g_sh.history)
		return ;
	ldl = g_sh.history->head;
	while (ldl && !ft_strstr(ldl->content, *to_find))
		ldl = ldl->next;
	ft_strdel(new);
	if (ldl)
		*new = ft_strdup(ldl->content);
}

static void	ft_delone_ctrlr(char **new, char **to_find, size_t *pos)
{	
	t_ldl	*ldl;
	char	*new_find;	

	ft_clear_prompt(NULL, 0, *pos, *new);
	(*pos)--;
	if (*pos)
	{
		new_find = ft_strndup(*to_find, *pos);
		ft_strdel(to_find);
		*to_find = ft_strdup(new_find);
		ft_strdel(&new_find);
	}
	else
		ft_strdel(to_find);
	ft_strdel(new);
	if (!g_sh.history || !(*to_find))
		return ;
	ldl = g_sh.history->head;
	while (ldl && !ft_strstr(ldl->content, *to_find))
		ldl = ldl->next;
	if (ldl)
		*new = ft_strdup(ldl->content);
}

char		history_ctrlr(t_buf *cmd, t_read *info, t_key *entry)
{
	char	*new;
	char	*to_find;
	int		ret;
	size_t	pos;

	DEBUG("OUI |%s|, prompt |%zu| win co |%zu| total char |%zu| curs |%zu| nread |%d|\n", cmd->cmd, info->prompt, info->win_co, info->total_char, info->curs_char, entry->nread);

	new = NULL;
	to_find = NULL;
	pos = 0;
	(void)entry;
	ft_clear_prompt(info, 1, 0, NULL);
	while (42)
	{
		ft_search_prompt(info, to_find, new, pos);
		ret = 0;
		read(0, &ret, sizeof(int));
		if (ft_isprint(ret))
			search_history(&new, &to_find, &pos, ret);
		else if (ret == 127 && pos)
		{
			ft_delone_ctrlr(&new, &to_find, &pos);
			tputs(g_termcaps_cap[LEFT], 0, &ft_putchar_termcap);
		}
		else if (ret != 127 && !ft_isprint(ret))
			break ;
	}
	ft_clear_prompt(info, 0, pos, new);
	prompt_display(info);
//	if (new)
//		display_str(cmd, info, new, ft_strlen(new));
	ft_strdel(&to_find);
	ft_strdel(&new);
	return (0);
}
