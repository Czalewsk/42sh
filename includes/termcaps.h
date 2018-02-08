/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:29:26 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/08 14:15:17 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TERMCAPS_H
# define __TERMCAPS_H

# include "ft_sh.h"

# define DEFAULT_TERMCAPS ("vt100")

typedef enum	e_termcaps_capability
{
	LEFT, RIGHT, DOWN, UP_CAP, COL, NDO, NUP, CLEAR, CLEAR_ALL, 
	HIGH_START, HIGH_STOP, LAST
}				t_termcaps_capability;

char	*g_termcaps_cap[LAST];

char		termcaps_init(char **env);
void		termcaps_restore_tty(void);

#endif
