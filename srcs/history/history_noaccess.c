/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_noaccess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:38:27 by bviala            #+#    #+#             */
/*   Updated: 2017/12/14 20:00:41 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	no_history_up(t_buf *cmd, t_read *info, int last)
{
	int len;

	len = ft_strlen(g_sh.h_save);
	if (!last)
	{
		while (g_sh.h_current &&
				ft_strncmp(g_sh.h_save, g_sh.h_current->content, len))
			g_sh.h_current = g_sh.h_current->next;
	}
	if (g_sh.h_current)
	{
		display_str(cmd, info, g_sh.h_current->content,
			ft_strlen(g_sh.h_current->content));
		if (g_sh.h_current->next)
			g_sh.h_current = g_sh.h_current->next;
	}
	return (0);
}

char	no_history_do(t_buf *cmd, t_read *info, int first)
{
	int len;
	
	len = ft_strlen(g_sh.h_save);
	if (!first)
	{
		while (g_sh.h_current &&
				ft_strncmp(g_sh.h_save, g_sh.h_current->content, len))
			g_sh.h_current = g_sh.h_current->prev;
	}
	if (g_sh.h_current)
	{
		display_str(cmd, info, g_sh.h_current->content,
			ft_strlen(g_sh.h_current->content));
		if (g_sh.h_current->prev)
			g_sh.h_current = g_sh.h_current->prev;
	}
	return (0);
}
