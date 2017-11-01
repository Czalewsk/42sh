/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:59:56 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/01 11:41:37 by czalewsk         ###   ########.fr       */
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


#define CTRL_KEY(k) ((k) & 0x1f)
#define SIZE_OF_READ (12)

char	*termcap = NULL;
struct termios s_termios;
struct termios s_termios_backup;

char	*left_cap = NULL;
char	*right_cap = NULL;
char	*up_cap = NULL;
char	*down_cap = NULL;
char	*clear_cap = NULL;
char	*nextline_cap = NULL;
char	*home_cap = NULL;
char	*test_cap = NULL;

void	init_term_cap(void)
{
	left_cap = tgetstr("le", NULL);
	right_cap = tgetstr("nd", NULL);
	down_cap = tgetstr("do", NULL);
	up_cap = tgetstr("up", NULL);
	clear_cap = tgetstr("cl", NULL);
	nextline_cap = tgetstr("sf", NULL);
	tputs(tgetstr("sc", NULL), 0, &ft_putchar_termcap);
	home_cap = tgetstr("rc", NULL);
	test_cap = tgetstr("cm", NULL);
	if (left_cap && down_cap && up_cap && right_cap && clear_cap && nextline_cap && 
			home_cap && test_cap)
		ft_printf("TERMCAP CAPABILITY DONE\r\n");
}

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
	if (ret)
		init_term_cap();
	return (ret);
}

void	restore_tty_param(void)
{
	tcsetattr(0, 0, &s_termios_backup);
}

void	debug_key(char key[SIZE_OF_READ], int nb)
{
	int i;

	i = 0;
	ft_printf("READ=%i\r\n", nb);
	while (i < nb)
		printf("%hhi\r\n", key[i++]);
}

void	set_tty(void)
{
	tcgetattr(0, &s_termios);
	tcgetattr(0, &s_termios_backup);
	s_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	s_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	s_termios.c_oflag &= ~(OPOST);
	s_termios.c_cflag |= (CS8);
	s_termios.c_cc[VMIN] = 0;
	s_termios.c_cc[VTIME] = 1;
	tcsetattr(0, 0, &s_termios);
}

int		read_key(char *c)
{
	int		nread;

	while ((nread = read(0, c, SIZE_OF_READ))  <= 0)
		if (nread == -1)
			ft_error(strerror(errno), &restore_tty_param);
	return (nread);
}

void	handle_arrow_key(char key)
{
	if (key == 68)
		tputs(left_cap, 0, &ft_putchar_termcap);
	if (key == 67)
		tputs(right_cap, 0, &ft_putchar_termcap);
	if (key == 72)
		tputs(home_cap, 0, &ft_putchar_termcap);
//	if (key == 65)
//		tputs(up_cap, 0, &ft_putchar_termcap);
//	if (key == 66)
//		tputs(down_cap, 0, &ft_putchar_termcap);
}

void	handler_cntrl_key(int nread, char c[SIZE_OF_READ])
{
	if (nread == 3 && c[0] == 27 && c[1] == 91)
		handle_arrow_key(c[2]);
	if (nread == 1 && *c == CTRL_KEY('k'))
		tputs(clear_cap, 0, &ft_putchar_termcap);
	if (nread == 1 && *c == 13)
		tputs(nextline_cap, 1, &ft_putchar_termcap);
	if (nread == 1 && *c == CTRL_KEY('x'))
		tputs(tgoto(test_cap, 1, 1), 1, &ft_putchar_termcap);
}

int		process_read_key(void)
{
	char	c[SIZE_OF_READ];
	int		nread;

	ft_bzero(&c, SIZE_OF_READ);
	nread = read_key((char*)c);
//	debug_key(c, nread);  //DEBUG
	if (nread == 1 && *c == CTRL_KEY('q'))
		return (0);
	if (nread <= sizeof(wint_t) && !ft_iswcntrl((int)*c))
		write(1, c, nread);
	else
		handler_cntrl_key(nread, c);
	return (1);
}

int		main(void)
{
	if (init_termcap() <= 0)
		return (1);
	set_tty();
	while (1)
		if (!process_read_key())
			break ;
	restore_tty_param();
}