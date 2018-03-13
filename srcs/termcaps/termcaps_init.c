/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:42:58 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/05 23:53:00 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static struct termios	s_termios_backup;
static struct termios	s_termios;

/*
**	int i = 0;
**	for (i = 0; i < CLEAR; i++)
**	{
**		if (!g_termcaps_cap[i])
**			DEBUG("TERMCAPS ERROR : (%d)\n", i); //DEBUG
**	}
*/

/*
**		Ancien mode bracketed
**		tputs("\e[?2005h", 0, &ft_putchar_termcap);
*/

/*
** Activation du mode : bracketed paste en fin d'initialisation
*/

static void				termcaps_cap_init(void)
{
	g_termcaps_cap[LEFT] = tgetstr("le", NULL);
	g_termcaps_cap[RIGHT] = tgetstr("nd", NULL);
	g_termcaps_cap[DOWN] = tgetstr("do", NULL);
	g_termcaps_cap[UP_CAP] = tgetstr("up", NULL);
	g_termcaps_cap[COL] = tgetstr("ch", NULL);
	g_termcaps_cap[NDO] = tgetstr("DO", NULL);
	g_termcaps_cap[NUP] = tgetstr("UP", NULL);
	g_termcaps_cap[CLEAR] = tgetstr("cd", NULL);
	g_termcaps_cap[CLEAR_ALL] = tgetstr("cl", NULL);
	if (tgetstr("te", NULL))
		tputs("\e[?2004h", 0, &ft_putchar_termcap);
	g_termcaps_cap[HIGH_START] = tgetstr("so", NULL);
	g_termcaps_cap[HIGH_STOP] = tgetstr("se", NULL);
	g_termcaps_cap[INV_ON] = tgetstr("vi", NULL);
	g_termcaps_cap[INV_OFF] = tgetstr("ve", NULL);
	g_termcaps_cap[SPE_ON] = tgetstr("te", NULL);
	g_termcaps_cap[SPE_OFF] = tgetstr("ti", NULL);
}

void					termcaps_backup_tty(void)
{
	tcgetattr(0, &s_termios_backup);
}

void					termcaps_restore_tty(void)
{
	tcsetattr(0, 0, &s_termios_backup);
}

void					termcaps_set_tty(void)
{
	tputs(tgetstr("rs", NULL), 1, &ft_putchar_termcap);
	tcsetattr(0, 0, &s_termios);
}

char					termcaps_init(void)
{
	int		ret;
	char	*env_term;

	termcaps_backup_tty();
	tcgetattr(0, &s_termios);
	s_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	s_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	s_termios.c_cflag |= (CS8);
	s_termios.c_cc[VMIN] = 1;
	s_termios.c_cc[VTIME] = 0;
	termcaps_set_tty();
	env_term = env_get("TERM");
	ret = tgetent(NULL, env_term ? env_term : DEFAULT_TERMCAPS);
	if (ret < 0)
		ft_error("Could not access the termcaps database",
				&termcaps_restore_tty);
	else if (!ret)
		ret = tgetent(NULL, DEFAULT_TERMCAPS);
	if (ret > 0)
		termcaps_cap_init();
	return (ret);
}
