/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:48:25 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/11 23:18:06 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		cursor_display_update(t_read *info, int write)
{
	int		forbidden_co;
	int		line;
	int		i;

		line = (info->total_char + info->prompt) / info->win_co;
		forbidden_co = ((info->curs_char + info->prompt + (line ? line - 1 : 0))
				% (info->win_co + 1) == info->win_co) ? 1 : 0;
		i = forbidden_co ? 0 : (info->curs_char + info->prompt) % info->win_co;
		DEBUG("VALUE TPUTS COL = %d\n", i)
		tputs(tparm(g_termcaps_cap[COL], i), 0, &ft_putchar_termcap);
		DEBUG("CURS_CHAR=%d | TOTAL_CHAR=%d | Totalchar with PRPT =%d\n", info->curs_char, info->total_char, info->total_char + info->prompt)
		DEBUG("(win=%d | forbidden=%d | LINE=%d)\n", info->win_co, forbidden_co, line)
	if (write)
	{
		i = ((info->curs_char + info->prompt + (line ? line - 1 : 0)) /
				info->win_co) - ((info->total_char + info->prompt + (line ? line - 1 : 0)) / info->win_co);
			if (i)
				tputs(tparm(g_termcaps_cap[i < 0 ? NUP : NDO], ABS(i)), 0,
						&ft_putchar_termcap);
		if (forbidden_co)
			tputs(g_termcaps_cap[DOWN], 0, &ft_putchar_termcap);
	}
	else
	{
		i = (((info->curs_char + info->prompt + (line ? line - 1 : 0)) /
				info->win_co) ? 0 : info->prompt) + 
				tputs(tparm(g_termcaps_cap[i < 0 ? NUP : NDO], ABS(i)), 1,
						&ft_putchar_termcap);
	}
}

char		curs_move_hz(t_buf *cmd, t_read *info, t_key *entry)
{
	int		mvt;

	(void)cmd;
	mvt = (entry->entry[2] == 68 ? -1 : 1);
	DEBUG("CURS_CHAR=%d | TOTAL_CHAR=%d | MVT=%+d | entry[2]=%hhd\n", info->curs_char, info->total_char, mvt, entry->entry[2])
	if (info->curs_char + mvt > (long)info->total_char || info->curs_char + mvt < 0)
		return (0);
	info->curs_char += mvt;
	cursor_display_update(info, 0);
		return (0);
}
