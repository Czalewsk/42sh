/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_noaccess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:38:27 by bviala            #+#    #+#             */
/*   Updated: 2018/03/19 15:09:11 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	no_history_up(t_buf *cmd, t_read *info, int last)
{
	if (!g_sh.h_current || (!last && !g_sh.h_current->next))
		return (0);
	if (!last && g_sh.h_first && g_sh.h_current->next)
		g_sh.h_current = g_sh.h_current->next;
	else if (last)
		g_sh.h_current = g_sh.history->tail;
	if (!g_sh.h_first)
		g_sh.h_first++;
	if (g_sh.h_current && !ft_strncmp(g_sh.h_save, g_sh.h_current->content,
				ft_strlen(g_sh.h_save)))
		display_str(cmd, info, g_sh.h_current->content,
				ft_strlen(g_sh.h_current->content));
	else if (g_sh.h_current)
	{
		if (last)
			return (no_history_do(cmd, info, 0));
		return (no_history_up(cmd, info, 0));
	}
	return (0);
}

char	no_history_do(t_buf *cmd, t_read *info, int first)
{
	if (!g_sh.h_current)
		return (0);
	if (!first && g_sh.h_current->prev)
		g_sh.h_current = g_sh.h_current->prev;
	else if (!first && !g_sh.h_current->prev)
	{
		display_str(cmd, info, g_sh.h_save, ft_strlen(g_sh.h_save));
		g_sh.h_first = 0;
		return (0);
	}
	else if (first)
		g_sh.h_current = g_sh.history->head;
	if (!ft_strncmp(g_sh.h_save, g_sh.h_current->content,
				ft_strlen(g_sh.h_save)))
		display_str(cmd, info, g_sh.h_current->content,
				ft_strlen(g_sh.h_current->content));
	else
	{
		if (first)
			return (no_history_up(cmd, info, 0));
		return (no_history_do(cmd, info, 0));
	}
	return (0);
}
