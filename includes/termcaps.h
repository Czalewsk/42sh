/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:29:26 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/06 16:12:34 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TERMCAPS_H
# define __TERMCAPS_H

# include "42shell.h"

typedef enum	e_termcaps_capability
{
	LEFT, RIGHT, DOWN, UP_CAP, COL, NDO, NUP, CLEAR
}				t_termcaps_capability;

char	*g_termcaps_cap[8];

#endif
