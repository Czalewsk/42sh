/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 04:42:37 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/26 17:53:40 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		cursor_back_home(t_read *info)
{
	int		line;

	tputs(tparm(g_termcaps_cap[COL], info->prompt), 0, &ft_putchar_termcap);
	if ((line = ((info->curs_char + info->prompt) / (info->win_co))))
		tputs(tparm(g_termcaps_cap[NUP], line), 0, &ft_putchar_termcap);
	tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
}

char		insert_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char	*curs;
	int		len;

	buff_handler(cmd, entry, NULL);
	cmd->size_actual += entry->nread;
	if (info->curs_char == (long)info->total_char)
	{
		cmd->cmd = ft_strncat(cmd->cmd, entry->entry, entry->nread);
		write(1, entry->entry, entry->nread);
	}
	else
	{
		len = sh_curs_unicode(cmd->cmd, info->curs_char, 0);
		curs = cmd->cmd + len;
		ft_memmove(curs + entry->nread, curs, sh_curs_unicode(cmd->cmd,
					ft_strlen(curs) + 1, 1));
		ft_memcpy(curs, entry->entry, entry->nread);
		cursor_back_home(info);
		write(1, cmd->cmd, cmd->size_actual);
	}
	info->curs_char++;
	info->total_char++;
	cursor_display_update(info, 1);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}

char		delete_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char		*curs;

	(void)entry;
	if (!cmd->cmd || !info->curs_char)
		return (0);
	curs = cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char, 1);
	ft_memmove(cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char - 1, 0),
			curs, ft_strlen(curs) + 1);
	cursor_back_home(info);
	cmd->size_actual = ft_strlen(cmd->cmd);
	write(1, cmd->cmd, cmd->size_actual);
	info->curs_char--;
	info->total_char = ft_strlen_utf8(cmd->cmd);
	cursor_display_update(info, 1);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}

char		suppr_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char		*curs;

	(void)entry;
	if (!cmd->cmd || (long)info->total_char == info->curs_char)
		return (0);
	curs = cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char, 0);
	ft_memmove(curs, cmd->cmd + sh_curs_unicode(cmd->cmd,
				info->curs_char + 1, 1), ft_strlen(curs) + 1);
	cmd->size_actual = ft_strlen(cmd->cmd);
	cursor_back_home(info);
	write(1, cmd->cmd, cmd->size_actual);
	info->total_char--;
	cursor_display_update(info, 1);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}
