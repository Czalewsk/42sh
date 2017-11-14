/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 04:42:37 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/14 17:23:55 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		cursor_back_home(t_read *info, int clean_screen)
{
	int		line;

	tputs(tparm(g_termcaps_cap[COL], info->prompt), 0, &ft_putchar_termcap);
	if ((line = ((info->curs_char + info->prompt) / (info->win_co))))
		tputs(tparm(g_termcaps_cap[NUP], line), 0, &ft_putchar_termcap);
	if (clean_screen)
		tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
}

char		insert_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char	*curs;

	buff_handler(cmd, entry);
	cmd->size_actual += entry->nread;
	if (info->curs_char == (long)info->total_char)
	{
		cmd->cmd = ft_strncat(cmd->cmd, entry->entry, entry->nread);
		write(1, entry->entry, entry->nread);
	}
	else
	{
		curs = cmd->cmd + info->curs_char;
		ft_memmove(curs + entry->nread, curs, ft_strlen(curs) + 1);
		ft_memcpy(curs, entry->entry, entry->nread);
		cursor_back_home(info, 1);
		write(1, cmd->cmd, cmd->size_actual);
	}
	info->curs_char++;
	info->total_char++;
	cursor_display_update(info, 1);
	return (1);
}

char		delete_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char		*curs;

	(void)entry;
	if (!cmd->cmd || !info->curs_char)
		return (1);
	curs = cmd->cmd + info->curs_char;
	ft_memmove(curs - 1, curs, ft_strlen(curs) + 1);
	cursor_back_home(info, 1);
	cmd->size_actual--;
	write(1, cmd->cmd, cmd->size_actual);
	info->curs_char--;
	info->total_char--;
	cursor_display_update(info, 1);
	return (1);
}

char		suppr_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char		*curs;

	(void)entry;
	if (!cmd->cmd || (long)info->total_char == info->curs_char)
		return (1);
	curs = cmd->cmd + info->curs_char;
	ft_memmove(curs, curs + 1, ft_strlen(curs + 1) + 1);
	cursor_back_home(info, 1);
	cmd->size_actual--;
	write(1, cmd->cmd, cmd->size_actual);
	info->total_char--;
	cursor_display_update(info, 1);
	return (1);
}
