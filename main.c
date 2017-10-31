/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:59:56 by czalewsk          #+#    #+#             */
/*   Updated: 2017/10/31 13:00:44 by czalewsk         ###   ########.fr       */
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


#define CTRL_KEY(k) ((k) & 0x1f)
#define SIZE_OF_READ (8)

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
//	cfmakeraw(&s_termios);
//	s_termios.c_lflag &= ~(ICANON);
//	s_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ECHOPRT);
	s_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	s_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	s_termios.c_oflag &= ~(OPOST);
	s_termios.c_cflag |= (CS8);
	s_termios.c_cc[VMIN] = 0;
	s_termios.c_cc[VTIME] = 1;
//	s_termios.c_lflag &= ~(ECHO);
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

int		process_read_key(void)
{
	char	c[SIZE_OF_READ];
	int		nread;

	ft_bzero(&c, SIZE_OF_READ);
	nread = read_key((char*)c);
	debug_key(c, nread);  //DEBUG
	if (nread == 1 && *c == CTRL_KEY('q'))
		return (0);
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