/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:18:46 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/07 09:48:42 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cedychou.h"
#include <fcntl.h>
#define DEBUG_WIN ("/dev/ttys005")

char	*left_cap = NULL;
char	*right_cap = NULL;
char	*insert_cap = NULL;
char	*exit_insert_cap = NULL;
char	*save_cursor_cap = NULL;
char	*restore_cursor_cap = NULL;
char	*begin_line_cap = NULL;
char	*down_cap = NULL;
char	*up_cap = NULL;
char	*col_cap = NULL;
char	*nleft_cap = NULL;
char	*ndo_cap = NULL;
char	*nup_cap = NULL;
char	*cl_line_cap = NULL;

void	debug_key(char key[SIZE_READ], int nb)
{
	int i;
	int fd;

	i = 0;
	fd = open(DEBUG_WIN, O_RDWR);
	dprintf(fd, "READ=%i\r\n", nb);
	while (i < nb)
		dprintf(fd, "%hhi\r\n", key[i++]);
	close(fd);
}

void	init_term_cap(void)
{
//	int fd;
//	fd = open(DEBUG_WIN, O_RDWR);
//	dprintf(fd, "\n\rPC=%c{%d} | UP=%s| BC=%s| ospeed=%hi\n", PC, PC, UP, BC, ospeed);
//	close(fd);
	left_cap = tgetstr("le", NULL);
	right_cap = tgetstr("nd", NULL);
	insert_cap = tgetstr("im", NULL);
	exit_insert_cap = tgetstr("ei", NULL);
	save_cursor_cap = tgetstr("sc", NULL);
	restore_cursor_cap = tgetstr("rc", NULL);
	begin_line_cap = tgetstr("cr", NULL);
	down_cap = tgetstr("do", NULL);
	up_cap = tgetstr("up", NULL);
	col_cap = tgetstr("ch", NULL);
	ndo_cap = tgetstr("DO", NULL);
	nup_cap = tgetstr("UP", NULL);
	cl_line_cap = tgetstr("cd", NULL);
	if (!left_cap || !right_cap || !insert_cap || !exit_insert_cap ||
			!save_cursor_cap || !restore_cursor_cap || !begin_line_cap ||
			!down_cap || !up_cap || !col_cap || !ndo_cap || !nup_cap ||
			!cl_line_cap)
		ft_printf("TERMCAP CAPABILITY ERROR\r\n");
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
	ret = tgetent(NULL, env_term);
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

void		read_key(t_key *entry)
{
	while ((entry->nread = read(0, entry->entry, SIZE_READ))  <= 0)
		if (entry->nread == -1)
			ft_error(strerror(errno), &restore_tty_param); // A recoder :D
}

/*
** Gere l'affichage des lignes
*/

void	handler_display_line(t_read *info, t_key *entry, t_buf *cmd, int del)
{
	long line;

	int fd;
	fd = open(DEBUG_WIN, O_RDWR);
	if (info->total_char  - 1 == info->curs_char && dprintf(fd, "write 1 char\n"))
		write(1, entry->entry, entry->nread);
	else
	{
	dprintf(fd, "win_co=%ld | curs_co=%ld | curs_li=%ld | prompt=%ld\n",
			info->win_co, info->curs_co, info->curs_li, info->prompt);
		line = ((info->total_char + info->prompt - 1) / info->win_co) -
			info->curs_li;
		tputs(tparm(col_cap, info->prompt), 0, &ft_putchar_termcap);
		if ((info->curs_li) && dprintf(fd, "nup info->curs_li\n")) //&& !(del && !info->curs_co))
			tputs(tparm(nup_cap, info->curs_li), 0, &ft_putchar_termcap);
		tputs(cl_line_cap, 1, &ft_putchar_termcap);
		write(1, cmd->cmd, cmd->size_actual);
		tputs(tparm(col_cap, info->curs_co +
			(info->curs_li ? 0 : info->prompt)), 0, &ft_putchar_termcap);
		if (line > 0 && dprintf(fd, "nup line > 0\n"))
			tputs(tparm(nup_cap, line), 0, &ft_putchar_termcap);
		if (del && info->curs_co == 0 && dprintf(fd, "new\n"))
			tputs(tparm(col_cap, info->win_co - 1), 0, &ft_putchar_termcap);
	}
	close(fd);
}

/*
** Gere le deplacement du curseur sur plusieurs lignes
*/

char	handler_cursor_pos(t_read *info, int mvt, int insert, int del)
{
	int fd;
	fd = open(DEBUG_WIN, O_RDWR);
	if (!insert && ((mvt > 0 && info->curs_char + mvt >= info->total_char + 1) ||
			(mvt < 0 && info->curs_char + mvt < 0)))
		return (0);
	info->curs_char += mvt;
	info->curs_co += mvt;
//	dprintf(fd, "win_co=%ld | curs_co=%ld | curs_li=%ld | prompt=%ld\n",
//			info->win_co, info->curs_co, info->curs_li, info->prompt);
	if (mvt > 0 && info->curs_co >= (long)(info->win_co - (info->curs_li ? 0 : info->prompt)))
	{
		dprintf(fd, "milieu ligne\n");
		tputs(down_cap, 0, &ft_putchar_termcap);
		tputs(tparm(col_cap, 0), 0, &ft_putchar_termcap);
		info->curs_li++;
		info->curs_co = 0;
	}
	else if (mvt < 0 && info->curs_co < 0)
	{
		dprintf(fd, "bas curseur\n");
		tputs(up_cap, 0, &ft_putchar_termcap);
		tputs(tparm(col_cap, info->win_co - 1), 0, &ft_putchar_termcap);
		info->curs_li--;
		info->curs_co = (info->win_co - 1) - (info->curs_li ? 0 : info->prompt);
	}
	else if (!insert)
		tputs((mvt > 0 ? right_cap : left_cap), 0, &ft_putchar_termcap);
	close(fd);
	return (1);
}

/*
** Gere les differentes touches avec les fleches
*/


char	arrow_handler(char key, t_read *info)
{
	int fd;
	fd = open(DEBUG_WIN, O_RDWR);
	if (key == 67)
		dprintf(fd, "~%d~\n", handler_cursor_pos(info, 1, 0, 0));
	if (key == 68)
		dprintf(fd, "~%d~\n", handler_cursor_pos(info, -1, 0, 0));
/*	if (key == 68 && info->curs_co > 0)
	{
		info->curs_co--;
		tputs(left_cap, 0, &ft_putchar_termcap);
	}
	if (key == 67 && info->curs_co < info->total_char)
	{
		info->curs_co++;
		tputs(right_cap, 0, &ft_putchar_termcap);
	}*/
	close(fd);
	return (0);
}


/*
** Switch entre les differents key handlers
*/

char	key_wrapper(t_key *entry, t_read *info)
{
	if (entry->nread == 1 && *(entry->entry) == 13)
		return (1);
	else if (entry->nread == 3 && entry->entry[0] == 27 && entry->entry[1] == 91)
		arrow_handler(entry->entry[2], info);
	return (2);
}

char	read_entry(t_buf *cmd, t_read *info, t_key *entry)
{
	read_key(entry);
//	debug_key(entry->entry, entry->nread);
	if (entry->nread == 1 && CTRL_KEY('d') == *(entry->entry))
		return (-1);
	if (entry->nread <= sizeof(wint_t) && 
			(!ft_iswcntrl((int)*(entry->entry)) || (int)*(entry->entry) == 127))
		return (0);
	else
		return (key_wrapper(entry, info)); // Switch entre les differents gestionnaires de touches
}

void	handler_buf(t_buf *cmd, t_key *entry)
{
	if (!entry)
	{
		cmd->size_max = SIZE_BUF_CMD;
		cmd->size_actual = 0;
		cmd->cmd = ft_strnew(SIZE_BUF_CMD);
		return ;
	}
	if (entry->nread + cmd->size_actual >= cmd->size_max - 1)
	{
		cmd->size_max *= 2;
		cmd->cmd = ft_memrealloc(cmd->cmd, cmd->size_actual, cmd->size_max);
	}
}


void	line_insert(t_buf *cmd, t_read *info, t_key *entry)
{
	char *curs;

	handler_buf(cmd, entry);
	info->total_char++;
	cmd->size_actual += entry->nread;
	if (info->curs_char == info->total_char - 1)
	{
		cmd->cmd = ft_strncat(cmd->cmd, entry->entry, entry->nread);
		handler_display_line(info, entry, cmd, 0);
		handler_cursor_pos(info, 1, 1, 0);
	}
	else
	{
		curs = cmd->cmd + info->curs_char;
		ft_memmove(curs + entry->nread, curs, ft_strlen(curs) + 1);
		ft_memcpy(curs, entry->entry, entry->nread);
		handler_display_line(info, entry, cmd, 0);
		handler_cursor_pos(info, 1, 0, 0);
	}
}

void	line_delete(t_buf *cmd, t_read *info, t_key *entry)
{
	char	*curs;
	char	len;
	int		line;

	int fd;
	fd = open(DEBUG_WIN, O_RDWR);
	if (!cmd->cmd || !info->curs_char)
		return ;
//	dprintf(fd, "info->total_char=%zd | info->curs_char=%zd, cmd is |%s|\n",
//			info->total_char, info->curs_char, cmd->cmd);
	info->total_char--;
	curs = cmd->cmd + info->curs_char;
	ft_memmove(curs - 1, curs, ft_strlen(curs) + 1);
	handler_display_line(info, entry, cmd, 1);
//	dprintf(fd, "info->total_char=%zd | info->curs_char=%zd, cmd is |%s|\n",
//			info->total_char, info->curs_char, cmd->cmd);
	handler_cursor_pos(info, -1, 0, 1);
	close(fd);
}

void	line_wrapper(t_buf *cmd, t_read *info, t_key *entry)
{
	int fd;
	fd = open(DEBUG_WIN, O_RDWR);
	dprintf(fd, "nread=%i | entry[0]=%hhi\n", entry->nread, entry->entry[0]);
	close(fd);
	if (entry->nread == 1 && entry->entry[0] == 127)
		line_delete(cmd, info, entry);
	else
		line_insert(cmd, info, entry);
}

char	read_line(t_buf *cmd, t_read *info)
{
	char	ret;
	t_key	entry;

	ret = 0;
	ft_bzero(&entry, sizeof(t_key));
	handler_buf(cmd, NULL);
	while (42)
	{
		if ((ret = read_entry(cmd, info, &entry)) == -1)
			break ;
		if (!ret)
			line_wrapper(cmd, info, &entry);
		else if (ret == 1)
			break ;
	}
//	ft_strdel(&cmd->cmd);
	return (ret);
}

void	sh_prompt(t_read *info)
{
	static int first;

	if (first++)
		write(1, "\n\r", 2);
	ft_putstr(PROMPT);
	info->prompt = ft_strlen(PROMPT);
//	tputs(save_cursor_cap, 0, &ft_putchar_termcap);
}

void	init_info(t_read *info)
{
	ft_bzero(info, sizeof(t_read));
	info->win_co = tgetnum("co");
}

int		main(void)
{
	t_buf			cmd;
	char	ret;
	t_read			info;

	set_tty();
	if (!init_termcap())
		return (1);
	while (42)
	{
		init_info(&info);
		sh_prompt(&info); // Envoyer la valeur de ret
		// A remplacer par une fonction qui return uniquement quand elle recoit un \n
		if ((ret = read_line(&cmd, &info)) <= -1)
			break ;
		ft_printf("\r\ncmd :|%s|", cmd.cmd); // DEBUG CMD
		ft_strdel(&cmd.cmd);
		// Execute a ret = cmd(&cmd);
	}
	restore_tty_param();
}
