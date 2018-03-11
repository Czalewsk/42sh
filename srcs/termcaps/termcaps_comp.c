/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_comp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:18:44 by bviala            #+#    #+#             */
/*   Updated: 2018/03/08 19:35:16 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		comp_reinit_tty(int signal)
{
	(void)signal;
	tputs(g_termcaps_cap[INV_OFF], 0, &ft_putchar_termcap);
}

void		comp_termcaps_set_tty(int signal)
{
	(void)signal;
	tputs(g_termcaps_cap[INV_ON], 0, &ft_putchar_termcap);
}
