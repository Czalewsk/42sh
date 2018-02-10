/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_pste_intern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:28:53 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/10 16:52:59 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char		g_copy_cut = 0;
static int		g_cpy_paste_cursor[2];

char		cpy_pst_mvt(t_buf *cmd, t_read *info, t_key *entry)
{
	int		start;
	int		end;

	if (entry)
	{
		g_sh.edition_state = NORMAL;
		key_manager(cmd, info, entry);
		g_sh.edition_state = COPY_PASTE;
	}
	g_cpy_paste_cursor[1] = sh_curs_unicode(cmd->cmd, info->curs_char, 0);
	start = g_cpy_paste_cursor[0] <= g_cpy_paste_cursor[1] ?
		g_cpy_paste_cursor[0] : g_cpy_paste_cursor[1];
	end = start == g_cpy_paste_cursor[0] ?
		g_cpy_paste_cursor[1] : g_cpy_paste_cursor[0];
	cursor_back_home(info);
	write(g_sh.fd_tty, cmd->cmd, start);
	tputs(g_termcaps_cap[HIGH_START], 0, &ft_putchar_termcap);
	write(g_sh.fd_tty, cmd->cmd + start, end - start);
	tputs(g_termcaps_cap[HIGH_STOP], 0, &ft_putchar_termcap);
	write(g_sh.fd_tty, cmd->cmd + end, cmd->size_actual - end);
	cursor_display_update(info, 1);
	return (1);
}

char		paste_intern(t_buf *cmd, t_read *info, t_key *entry)
{
	char	*curs;
	int		len;
	int		size_paste;
	int		size_visu;

	ft_bzero(entry, sizeof(t_key));
	if (!g_sh.pasted || !(size_paste = ft_strlen(g_sh.pasted)))
		return (1);
	buff_handler(cmd, NULL, g_sh.pasted);
	cmd->size_actual += size_paste;
	len = sh_curs_unicode(cmd->cmd, info->curs_char, 0);
	curs = cmd->cmd + len;
	ft_memmove(curs + size_paste, curs, ft_strlen(curs));
	ft_memcpy(curs, g_sh.pasted, size_paste);
	cursor_back_home(info);
	write(g_sh.fd_tty, cmd->cmd, len);
	tputs(g_termcaps_cap[HIGH_START], 0, &ft_putchar_termcap);
	write(g_sh.fd_tty, curs, size_paste);
	tputs(g_termcaps_cap[HIGH_STOP], 0, &ft_putchar_termcap);
	write(g_sh.fd_tty, curs + size_paste, cmd->size_actual - len - size_paste);
	size_visu = ft_strlen_utf8(g_sh.pasted);
	(info->curs_char += size_visu) && (info->total_char += size_visu);
	cursor_display_update(info, 1);
	g_sh.edition_state = PASTED;
	return (1);
}

char		cpy_cut_validate(t_buf *cmd, t_read *info, t_key *entry)
{
	int		start;
	int		end;

	if (entry->nread == 6)
		g_copy_cut = entry->entry[5] - 79;
	start = (g_cpy_paste_cursor[0] <= g_cpy_paste_cursor[1]) ?
		g_cpy_paste_cursor[0] : g_cpy_paste_cursor[1];
	end = (start == g_cpy_paste_cursor[0]) ?
		g_cpy_paste_cursor[1] : g_cpy_paste_cursor[0];
	ft_strdel(&g_sh.pasted);
	g_sh.pasted = ft_strsub(cmd->cmd, start, end - start);
	if (g_copy_cut == 1)
	{
		g_sh.edition_state = NORMAL;
		ft_memmove(cmd->cmd + start, cmd->cmd + end,
				cmd->size_actual - end + 2);
		display_str(cmd, info, NULL,
				info->curs_char - ft_strlen_utf8(g_sh.pasted));
	}
	else
		pasted_remove_highlight_char(cmd, info, entry);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}

char		cpy_cut_intern(t_buf *cmd, t_read *info, t_key *entry)
{
	if (info->total_char)
	{
		if (g_sh.edition_state == COPY_PASTE)
			cpy_cut_validate(cmd, info, entry);
		else
		{
			g_sh.edition_state = COPY_PASTE;
			ft_bzero(g_cpy_paste_cursor, sizeof(g_cpy_paste_cursor));
			g_copy_cut = entry->entry[5] - 79;
			g_cpy_paste_cursor[0] = sh_curs_unicode(cmd->cmd,
					info->curs_char, 0);
			cpy_pst_mvt(cmd, info, NULL);
		}
	}
	ft_bzero(entry, sizeof(t_key));
	return (1);
}
