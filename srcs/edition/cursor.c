/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:48:25 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/13 19:11:42 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		calcul_line(t_read *info, int write)
{
	static int		line;
	int		line_max;
	int		ret;

	ret = 0;
	if (write)
	{
		line = ((info->curs_char + info->prompt) / (info->win_co));
		line_max = ((info->total_char + info->prompt - 1) / (info->win_co));
		ret = line - line_max;
	}
	else
	{
		line_max = ((info->curs_char + info->prompt) / (info->win_co));
		ret = line_max - line;
		line = line_max;
	}
	return (ret);
}

void		cursor_display_update(t_read *info, int write)
{
	int		forbidden_co;
	int		line;
	int		i;

	line = (info->curs_char + info->prompt + 1) / info->win_co;
	forbidden_co = ((size_t)line == info->win_co) ? 1 : 0;
	i = forbidden_co ? 0 : (info->curs_char + info->prompt) % info->win_co;
	tputs(tparm(g_termcaps_cap[COL], i), 0, &ft_putchar_termcap);
	line = calcul_line(info, write);
	if (line == 1)
		tputs(g_termcaps_cap[DOWN], 0, &ft_putchar_termcap);
	else if (line)
		tputs(tparm(g_termcaps_cap[line < 0 ? NUP : NDO], ABS(line)), 1,
						&ft_putchar_termcap);
}

char		curs_move_hz(t_buf *cmd, t_read *info, t_key *entry)
{
	int		mvt;

	(void)cmd;
	mvt = (entry->entry[2] == 68 ? -1 : 1);
	if (info->curs_char + mvt > (long)info->total_char
			|| info->curs_char + mvt < 0)
		return (0);
	info->curs_char += mvt;
	cursor_display_update(info, 0);
		return (0);
}
