/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:42:58 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/04 19:18:52 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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

static void		termcaps_cap_init(void)
{
	g_termcaps_cap[LEFT] = tgetstr("le", NULL);
	g_termcaps_cap[RIGHT] = tgetstr("nd", NULL);
	g_termcaps_cap[DOWN] = tgetstr("do", NULL);
	g_termcaps_cap[UP_CAP] = tgetstr("up", NULL);
	g_termcaps_cap[COL] = tgetstr("ch", NULL);
	g_termcaps_cap[NDO] = tgetstr("DO", NULL);
	g_termcaps_cap[NUP] = tgetstr("UP", NULL);
	g_termcaps_cap[CLEAR] = tgetstr("cd", NULL);
	if (tgetstr("te", NULL))
		tputs("\e[?2004h", 0, &ft_putchar_termcap);
}

static void		termcaps_set_tty(void)
{
	struct termios			s_termios;

	tcgetattr(0, &s_termios);
	termcaps_restore_tty();
	s_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	s_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	s_termios.c_cflag |= (CS8);
	s_termios.c_cc[VMIN] = 1;
	s_termios.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &s_termios);
}

char			termcaps_init(char **env)
{
	int		ret;
	char	*env_term;

	termcaps_set_tty();
	env_term = ft_getenv(env, "TERM");
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

void			termcaps_restore_tty(void)
{
	static struct termios	s_termios_backup;
	static	int				i;

	if (!i++)
		tcgetattr(0, &s_termios_backup);
	else
		tcsetattr(0, 0, &s_termios_backup);
}
