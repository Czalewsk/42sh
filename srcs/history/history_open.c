/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:06:53 by bviala            #+#    #+#             */
/*   Updated: 2017/12/12 23:21:52 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		check_history_access(const char *file)
{
	struct stat buff;

	errno = 0;
	if (!stat(file, &buff))
	{
		if (S_ISREG(buff.st_mode) && (S_IRUSR & buff.st_mode))
			return (1);
		else
			return (0);
	}
	if (errno == 2)
		return (1);
	return (0);
}

char	no_history_up(t_buf *cmd, t_read *info, int last)
{
	int len;
	size_t i;
	t_ldl *temp;

	i = g_sh.hist_i;
	temp = g_sh.hist_current;
	len = (info->curs_char) ? info->curs_char : ft_strlen(cmd->cmd);
	if (last)
	{
		temp = g_sh.hist->tail;
		i = g_sh.hist->length;
		while (temp->prev)
		{
			temp = temp->prev;
			i--;
			if (!ft_strncmp(temp->content, cmd->cmd, len))
				break ;
		}
	}
	else
	{
		while (temp->next) 
		{
			temp = temp->next;
			i++;
			if (!ft_strncmp(temp->content, cmd->cmd, len))
				break ;
		}
	}
	if (temp)
	{
		g_sh.hist_current = temp;
		g_sh.hist_i = i;
		display_str(cmd, info, g_sh.hist_current->content,
			ft_strlen(g_sh.hist_current->content));
	}
	return (0);
}

char	no_history_do(t_buf *cmd, t_read *info, int first)
{
	int len;
	size_t i;
	t_ldl *temp;

	i = g_sh.hist_i;
	temp = g_sh.hist_current;
	len = (info->curs_char) ? info->curs_char : ft_strlen(cmd->cmd);
	if (first)
	{
		temp = g_sh.hist->head;
		i = 1;
		while (temp->next)
		{
			temp = temp->next;
			i++;
			if (!ft_strncmp(temp->content, cmd->cmd, len))
				break ;
		}
	}
	else
	{
		while (temp->prev) 
		{
			temp = temp->prev;
			i--;
			if (!ft_strncmp(temp->content, cmd->cmd, len))
				break ;
		}
	}
	if (temp)
	{
		g_sh.hist_current = temp;
		g_sh.hist_i = i;
		display_str(cmd, info, g_sh.hist_current->content,
			ft_strlen(g_sh.hist_current->content));
	}
	return (0);
}
