/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_comp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:15:22 by bviala            #+#    #+#             */
/*   Updated: 2018/03/08 18:30:17 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		comp_signal(t_buf *cmd, t_read *info)
{
	t_ldl			*ldl;
	struct winsize	ws;

	ioctl(g_sh.fd_tty, TIOCGWINSZ, &ws) ? ft_bzero(&ws, sizeof(ws)) : 0;
	info->win_co = ws.ws_col;
	info->win_height = ws.ws_row - 1;
	calcul_display(g_sh.comp, info, cmd);
	ldl = (g_sh.comp->head) ? g_sh.comp->head->head : NULL;
	if (ldl)
	{
		tputs(g_termcaps_cap[CLEAR_ALL], 0, &ft_putchar_termcap);
		cursor_back_begin(info);
		prompt_display(info, 0);
		g_sh.comp->first = 1;
		ft_putstr_fd(cmd->cmd, g_sh.fd_tty);
		ft_putchar_fd('\n', g_sh.fd_tty);
		print_comp(g_sh.comp, info, cmd);
	}
}
