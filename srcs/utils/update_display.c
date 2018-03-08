/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:26:01 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/08 19:25:10 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_read		*g_save_info;
t_buf		*g_save_cmd;

void		update_display_init(t_read *info, t_buf *cmd)
{
	g_save_info = info;
	g_save_cmd = cmd;
}

void		update_display(void)
{
	struct winsize	ws;

	cursor_back_home(g_save_info, 0);
	ioctl(g_sh.fd_tty, TIOCGWINSZ, &ws) ? ft_bzero(&ws, sizeof(ws)) : 0;
	g_save_info->win_co = ws.ws_col;
	g_save_info->win_height = ws.ws_row - 1;
	prompt_display(g_save_info, 0);
	write(g_sh.fd_tty, g_save_cmd->cmd, g_save_cmd->size_actual);
	cursor_display_update(g_save_info, 1);
}
