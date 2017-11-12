/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:48:25 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/12 20:05:34 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		calcul_line(t_read *info, int write)
{
	int		line;
	int		line_max;
	int		ret;
	int		i;

	ret = 0;
	if (write)
	{
		i = (info->total_char + info->prompt) % info->win_co;
		line_max = ((info->total_char + info->prompt) /
			info->win_co) + (i ? 1 : 0);
		i = (info->curs_char + info->prompt) % info->win_co;
		line = ((info->curs_char + info->prompt) /
			info->win_co) + (i ? 1 : 0);
		ret = line - line_max;
		DEBUG("line=%d | max=%d\n", line, line_max)
	}
	else
	{
	}
	return (ret);
}

void		cursor_display_update(t_read *info, int write)
{
	int		forbidden_co;
	int		line;
	int		i;

	line = (info->total_char + info->prompt) / info->win_co;
	forbidden_co = ((info->curs_char + info->prompt + (line ? line - 1 : 0))
			% (info->win_co + 1) == info->win_co) ? 1 : 0;
	i = forbidden_co ? 0 : (info->curs_char + info->prompt) % info->win_co;
	tputs(tparm(g_termcaps_cap[COL], i), 0, &ft_putchar_termcap);
	line = calcul_line(info, write);
	if (line)
	{
		tputs(tparm(g_termcaps_cap[line < 0 ? NUP : NDO], ABS(line)), 0,
						&ft_putchar_termcap);
	}
	if (write && forbidden_co)
	{
		tputs(g_termcaps_cap[DOWN], 0, &ft_putchar_termcap);
	}
/*	{
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
						&ft_putchar_termcap);*/
}

char		curs_move_hz(t_buf *cmd, t_read *info, t_key *entry)
{
	int		mvt;

	(void)cmd;
	mvt = (entry->entry[2] == 68 ? -1 : 1);
	if (info->curs_char + mvt > (long)info->total_char || info->curs_char + mvt < 0)
		return (0);
	info->curs_char += mvt;
	cursor_display_update(info, 0);
		return (0);
}
