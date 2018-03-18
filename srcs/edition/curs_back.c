/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 19:38:32 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/17 17:18:29 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		cursor_back_home(t_read *info, char after_prompt)
{
	int		line;

	if (!info->win_co)
		return ;
	tputs(tparm(g_termcaps_cap[COL], after_prompt ?
				info->prompt % info->win_co : 0), 0,
			&ft_putchar_termcap);
	if ((line = ((info->curs_char + info->prompt) / info->win_co) -
				(info->prompt / info->win_co)))
		tputs(tparm(g_termcaps_cap[NUP], line), 0, &ft_putchar_termcap);
	tputs(tgetstr("ce", NULL), 0, &ft_putchar_termcap);
	tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
}

void		cursor_back_begin(t_read *info)
{
	int		line;

	if (!info->win_co)
		return ;
	tputs(tparm(g_termcaps_cap[COL], 0), 0, &ft_putchar_termcap);
	if ((line = ((info->curs_char + info->prompt) / info->win_co) -
				(info->prompt / info->win_co)))
		tputs(tparm(g_termcaps_cap[NUP], line), 0, &ft_putchar_termcap);
	tputs(g_termcaps_cap[CLEAR], 0, &ft_putchar_termcap);
}
