/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:29:26 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/05 23:57:40 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TERMCAPS_H
# define __TERMCAPS_H

# include "ft_sh.h"

# define DEFAULT_TERMCAPS ("vt100")

typedef enum	e_termcaps_capability
{
	LEFT, RIGHT, DOWN, UP_CAP, COL, NDO, NUP, CLEAR, CLEAR_ALL,
	HIGH_START, HIGH_STOP, INV_ON, INV_OFF, SPE_ON, SPE_OFF, LAST
}				t_termcaps_capability;

char	*g_termcaps_cap[LAST];

char		termcaps_init();
void		termcaps_restore_tty(void);
void		termcaps_set_tty(void);

void		comp_termcaps_set_tty(int signal);
void		comp_reinit_tty(int signal);
#endif
