/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:59:56 by czalewsk          #+#    #+#             */
/*   Updated: 2017/10/31 08:55:13 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <termcap.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <wctype.h>

#define CTRL_KEY(k) ((k) & 0x1f)

char	*termcap = NULL;
struct termios s_termios;
struct termios s_termios_backup;

char	init_termcap(void)
{
	int		ret;
	char	*env_term;

	if(!(env_term = getenv("TERM")))
	{
		ft_printf("NO TERM IN ENV\n");
		return (-1);
	}
	termcap = NULL;
	ret = tgetent(termcap, env_term);
	if (ret < 0)
		ft_printf("Could not access the termcaps database\n");
	else if (!ret)
		ft_printf("Terminale %s is not documented\n", env_term);
	return (ret);
}

void testTextColorAndEffect()
{
	char *af_cmd = tgetstr("AF", &termcap);
	char *reset_cmd = tgetstr("me", &termcap);
	char *blink_cmd = tgetstr("mb", &termcap);
	char *bold_cmd = tgetstr("md", &termcap);
	char *underline_cmd = tgetstr("us", &termcap);

	tputs(tparm(af_cmd, COLOR_RED), 1, putchar);
	printf("Texte rouge\n");

	tputs(tparm(af_cmd, COLOR_GREEN), 1, putchar);
	printf("Texte vert\n");

	tputs(tparm(af_cmd, COLOR_BLUE), 1, putchar);
	printf("Texte bleu\n");

	tputs(reset_cmd, 1, putchar);
	tputs(blink_cmd, 1, putchar);
	printf("Texte clignotant\n");

	tputs(tparm(af_cmd, COLOR_GREEN), 1, putchar);
	printf("Texte vert clignotant\n");

	tputs(reset_cmd, 1, putchar);
	tputs(bold_cmd, 1, putchar);
	printf("Texte en gras\n");

	tputs(tparm(af_cmd, COLOR_RED), 1, putchar);
	printf("Texte rouge en gras\n");

	tputs(reset_cmd, 1, putchar);
	tputs(tparm(af_cmd, COLOR_GREEN), 1, putchar);
	tputs(underline_cmd, 1, putchar);
	printf("Texte vert souligné\n");

	tputs(tparm(af_cmd, COLOR_BLUE), 1, putchar);
	tputs(bold_cmd, 1, putchar);
	tputs(blink_cmd, 1, putchar);
	tputs(underline_cmd, 1, putchar);
	printf("Texte blue en gras souligné clignotant\n");
	tputs(reset_cmd, 1, putchar);
}

void	print_window(void)
{
	int		co;
	int		li;
	int		i;

	co = tgetnum("co");
	li = tgetnum("li");
	i = 0;
	ft_printf("Nombre de ligne = %d | Nbr de col = %d\r\n", li, co);
	while (++i <= co)
		ft_putnbr(i % 10);
	i = 2;
	write(1, "\n", 1);
	while (++i <= li)
	{
		ft_putnbr(i);
		write(1, "\r\n", 2);
	}
}

void	set_tty(void)
{
	tcgetattr(0, &s_termios);
	tcgetattr(0, &s_termios_backup);
//	cfmakeraw(&s_termios);
//	s_termios.c_lflag &= ~(ICANON);
//	s_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ECHOPRT);
	s_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	s_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	s_termios.c_oflag &= ~(OPOST);
	s_termios.c_cflag |= (CS8);
//	s_termios.c_lflag &= ~(ECHO);
	tcsetattr(0, 0, &s_termios);
}

int		main(void)
{
	unsigned long int		i;

	if (init_termcap() <= 0)
		return (1);
	print_window();
//	testTextColorAndEffect();
	set_tty();
	while (1)
	{
		i = 0;
		read(0, &i, sizeof(i));
		ft_printf("READ=%d | char {{", i);
		if (!iswcntrl(i))
			write(1, &i, sizeof(i));
		ft_putendl("}\r");
		if (i == CTRL_KEY('q'))
			return (0);
	}
	tcsetattr(0, 0, &s_termios_backup);
}