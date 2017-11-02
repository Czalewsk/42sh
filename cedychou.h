/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cedychou.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:28:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/02 19:17:57 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <termcap.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <wctype.h>
#include <string.h>
#include <errno.h>
#include <xlocale.h>
#include <locale.h>
#include <wctype.h>

/*
** TERMINAL MODIFICATION GLOBAL STRUCTURE OF THE DEATH
*/

struct termios s_termios;
struct termios s_termios_backup;


/*
**	READ DEFINE OF BENYCHoOOU BRO DU GAME TU PESE
*/

#define SIZE_READ (12)
#define CTRL_KEY(k) ((k) & 0x1f)


/*
** PROMPT
*/

#define PROMPT ("Cedychou_sh 🦆  ")


/*
** Edition de ligne
*/

typedef struct		s_read
{
	size_t		prompt;
	size_t		li;
	size_t		co;
	size_t		curs_li;
	size_t		curs_co;
	size_t		total_char;
}					t_read;

typedef struct		s_key
{
	int			nread;
	char		entry[SIZE_READ];
}					t_key;
