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

#define PROMPT ("Cedychou_sh 🦆  ")

void	debug_key(char key[SIZE_READ], int nb)
{
	int i;

	i = 0;
	ft_printf("READ=%i\r\n", nb);
	while (i < nb)
		printf("%hhi\r\n", key[i++]);
}

void	restore_tty_param(void)
{
	tcsetattr(0, 0, &s_termios_backup);
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

	while ((nread = read(0, c, SIZE_READ))  <= 0)
		if (nread == -1)
			ft_error(strerror(errno), &restore_tty_param); // A recoder :D
	return (nread);
}

/*
**  Gere l'affichage et le deplacement du cursor (retour a la ligne...)
*/

void	sh_print_char(int nread, char entry[SIZE_READ])
{
	return ;
}

/*
** Gere les differentes combinaisons de touches avec CONTROL
*/

char	cntrl_handler(int nread, char entry[SIZE_READ])
{
	return (0);
}

/*
** Switch entre les differents key handlers
*/

char	key_wrapper(int nread, char entry[SIZE_READ])
{

	return (0);
}

unsigned char	read_entry(char **cmd)
{
	int		nread;
	char	entry[SIZE_READ];
	char	a;

	(void)cmd;
	nread = read_key((char*)entry);
	if (nread == 1 && CTRL_KEY('a') == *entry)
		return (0);
	if (nread <= sizeof(wint_t) && !ft_iswcntrl((int)*entry))
		sh_print_char(nread, entry);
	else
		a = key_wrapper(nread, entry); // Switch entre les differents gestionnaires de touches
	return (a);
}

void	sh_prompt(void)
{
	ft_putstr(PROMPT);
}

int		main(void)
{
	char			*cmd;
	unsigned char	ret;

	cmd = NULL;
	set_tty();
	sh_prompt(); // Envoyer la valeur de ret et include dans la boucle
	while (42)
	{
		// A remplacer par une fonction qui return uniquement quand elle recoit un \n
		if (!(ret = read_entry(&cmd)))
			break ;
		// Execute a ret = cmd(&cmd);
	}
	restore_tty_param();
}
