/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 04:42:37 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/12 20:14:46 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		insert_char(t_buf *cmd, t_read *info, t_key *entry)
{
	int		line;
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
		line = (info->curs_char + info->prompt) % info->win_co;
		line = ((info->curs_char + info->prompt + 1) /
			info->win_co);
		DEBUG("--LINE=%d|\n", line)
		curs = cmd->cmd + info->curs_char;
		ft_memmove(curs + entry->nread, curs, ft_strlen(curs) + 1);
		ft_memcpy(curs, entry->entry, entry->nread);
		tputs(tparm(g_termcaps_cap[COL], info->prompt), 0, &ft_putchar_termcap);
		if (line - 1)
			tputs(tparm(g_termcaps_cap[NUP], line - 1), 0, &ft_putchar_termcap);
		tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
		write(1, cmd->cmd, cmd->size_actual);
	}
	info->curs_char++;
	info->total_char++;
	cursor_display_update(info, 1);
	return (1);
}
