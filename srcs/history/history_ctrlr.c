/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_ctrlr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 15:51:28 by bviala            #+#    #+#             */
/*   Updated: 2018/01/09 21:38:22 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				g_up_max = 0;

static void	ft_clear_prompt(t_read *info, int first, size_t pos, char *new)
{
	int			up;

	if (!first)
	{
		info->prompt = 22 + pos;
		if (new)
			info->curs_char = ft_strlen_utf8(new);
		else
			info->curs_char = 0;
	}
	if (info->prompt + info->curs_char > info->win_co)
	{
		up = (info->prompt + info->curs_char) / info->win_co;
		tputs(tparm(g_termcaps_cap[COL], 0), 0, &ft_putchar_termcap);
		if (up > g_up_max)
			up = g_up_max;
			tputs(tparm(g_termcaps_cap[NUP], up), 0, &ft_putchar_termcap);
		tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
	}
	else
		cursor_back_begin(info);
	g_up_max = 0;
}

static void	ft_search_prompt(char *to_find, char *new)
{
	if (to_find)
	{
		ft_printf("(reverse-i-search)`%s': ", to_find);
		if (new)
			ft_putstr(new);
	}
	else
		ft_putstr("(reverse-i-search)`': ");
}

static void	search_history(char **new, char **to_find, t_read *info, int ret)
{
	char	tmp[2];
	t_ldl	*ldl;
	int		up;

	up = 0;
	tmp[0] = (char)ret;
	tmp[1] = '\0';
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
	if ((up = ((ft_strlen(*new) + ft_strlen(*to_find) + 22) / info->win_co))
		&& (up > g_up_max))
		g_up_max = up;
}

static void	ft_delone_ctrlr(char **new, char **to_find,
		size_t *pos, t_read *info)
{
	t_ldl	*ldl;
	char	*new_find;

//	ft_clear_prompt(info, 0, *pos, *new);
	(void)info;
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

	new = NULL;
	to_find = NULL;
	pos = 0;
	(void)entry;
	ft_clear_prompt(info, 1, 0, NULL);
	while (42)
	{
		ft_search_prompt(to_find, new);
		ret = 0;
		read(0, &ret, sizeof(int));
		if (ft_isprint(ret))
		{
			ft_clear_prompt(info, 0, pos, new);
			search_history(&new, &to_find, info, ret);
			pos++;
		}
		else if (ret == 127 && pos)
		{
			ft_clear_prompt(info, 0, pos, new);
			pos--;
			ft_delone_ctrlr(&new, &to_find, &pos, info);
		}
		else if (ret == 127 && !pos)
			ft_clear_prompt(info, 0, pos, new);
		else if (ret != 127 && !ft_isprint(ret))
			break ;
	}
	ft_clear_prompt(info, 0, pos, new);
	prompt_display(info, 0);
	if (new)
		display_str(cmd, info, new, ft_strlen(new));
	ft_strdel(&to_find);
	ft_strdel(&new);
	return (0);
}
