/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:29:26 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/06 17:41:40 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TERMCAPS_H
# define __TERMCAPS_H

# include "ft_sh.h"

# define DEFAULT_TERMCAPS ("vt100")

typedef enum	e_termcaps_capability
{
	LEFT, RIGHT, DOWN, UP_CAP, COL, NDO, NUP, CLEAR
}				t_termcaps_capability;

char	*g_termcaps_cap[8];

char		termcaps_init(char **env);
void		termcaps_restore_tty(void);

#endif
