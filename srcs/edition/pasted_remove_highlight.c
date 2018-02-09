/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasted_remove_highlight.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:44:18 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/09 02:22:10 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		pasted_remove_highlight_char(t_buf *cmd, t_read *info, t_key *entry)
{
	g_sh.edition_state = NORMAL;
	(void)entry;
	cursor_back_home(info);
	write(g_sh.fd_tty, cmd->cmd, cmd->size_actual);
	cursor_display_update(info, 1);
	return (1);
}

char		pasted_remove_highlight(t_buf *cmd, t_read *info, t_key *entry)
{
	g_sh.edition_state = NORMAL;
	(void)entry;
	cursor_back_home(info);
	write(g_sh.fd_tty, cmd->cmd, cmd->size_actual);
	cursor_display_update(info, 1);
	return (key_manager(cmd, info, entry));
}
