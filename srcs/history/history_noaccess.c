/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_noaccess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:38:27 by bviala            #+#    #+#             */
/*   Updated: 2017/12/14 18:09:29 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	no_history_up(t_buf *cmd, t_read *info, int last)
{
	int len;
	t_ldl *temp;

	temp = g_sh.hist_current;
	len = (info->curs_char) ? info->curs_char : ft_strlen(cmd->cmd);
	if (last)
	{
		temp = g_sh.hist->tail;
		while (temp->prev)
		{
			temp = temp->prev;
			if (!ft_strncmp(temp->content, cmd->cmd, len))
				break ;
		}
	}
	else
	{
		while (temp->next) 
		{
			temp = temp->next;
			if (!ft_strncmp(temp->content, cmd->cmd, len))
				break ;
		}
	}
	if (temp)
	{
		g_sh.hist_current = temp;
		display_str(cmd, info, g_sh.hist_current->content,
			ft_strlen(g_sh.hist_current->content));
	}
	return (0);
}

char	no_history_do(t_buf *cmd, t_read *info, int first)
{
	int len;
	t_ldl *temp;

	temp = g_sh.hist_current;
	len = (info->curs_char) ? info->curs_char : ft_strlen(cmd->cmd);
	if (first)
	{
		temp = g_sh.hist->head;
		while (temp->next)
		{
			temp = temp->next;
			if (!ft_strncmp(temp->content, cmd->cmd, len))
				break ;
		}
	}
	else
	{
		while (temp->prev) 
		{
			temp = temp->prev;
			if (!ft_strncmp(temp->content, cmd->cmd, len))
				break ;
		}
	}
	if (temp)
	{
		g_sh.hist_current = temp;
		display_str(cmd, info, g_sh.hist_current->content,
			ft_strlen(g_sh.hist_current->content));
	}
	return (0);
}
