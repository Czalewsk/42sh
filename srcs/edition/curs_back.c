/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 19:38:32 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/09 21:38:25 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		cursor_back_home(t_read *info)
{
	int		line;

	tputs(tparm(g_termcaps_cap[COL], info->prompt % info->win_co), 0,
			&ft_putchar_termcap);
	if ((line = ((info->curs_char + info->prompt) / info->win_co) -
				(info->prompt / info->win_co)))
		tputs(tparm(g_termcaps_cap[NUP], line), 0, &ft_putchar_termcap);
	tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
}

void		cursor_back_begin(t_read *info)
{
	int		line;

	tputs(tparm(g_termcaps_cap[COL], 0), 0, &ft_putchar_termcap);
	if ((line = ((info->curs_char + info->prompt) / info->win_co) -
				(info->prompt / info->win_co)))
		tputs(tparm(g_termcaps_cap[NUP], line), 0, &ft_putchar_termcap);
	tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
}
