/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:18:46 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/03 18:16:25 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cedychou.h"

char	*left_cap = NULL;
char	*right_cap = NULL;
char	*insert_cap = NULL;
char	*exit_insert_cap = NULL;

void	debug_key(char key[SIZE_READ], int nb)
{
	int i;

	i = 0;
	ft_printf("READ=%i\r\n", nb);
	while (i < nb)
		printf("%hhi\r\n", key[i++]);
}

void	init_term_cap(void)
{
	ft_printf("STRANGE:%i\n\r", tgetflag("xn"));
	left_cap = tgetstr("le", NULL);
	right_cap = tgetstr("nd", NULL);
	insert_cap = tgetstr("im", NULL);
	exit_insert_cap = tgetstr("ei", NULL);
	if (!left_cap || !right_cap || !insert_cap || !exit_insert_cap)
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
** Gere les differentes touches avec les fleches
*/

char	arrow_handler(char key, t_read *info)
{
	if (key == 68 && info->curs_co > 0)
	{
		info->curs_co--;
		tputs(left_cap, 0, &ft_putchar_termcap);
	}
	if (key == 67 && info->curs_co < info->total_char)
	{
		info->curs_co++;
		tputs(right_cap, 0, &ft_putchar_termcap);
	}
	return (0);
}


/*
** Switch entre les differents key handlers
*/

char	key_wrapper(t_key *entry, t_read *info)
{
	if (entry->nread == 1 && *(entry->entry) == 13)
		return (1);
	if (entry->nread == 3 && entry->entry[0] == 27 && entry->entry[1] == 91)
		arrow_handler(entry->entry[2], info);
	return (0);
}

char	read_entry(t_buf *cmd, t_read *info, t_key *entry)
{
	read_key(entry);
	if (entry->nread == 1 && CTRL_KEY('d') == *(entry->entry))
		return (-1);
	if (entry->nread <= sizeof(wint_t) && !ft_iswcntrl((int)*(entry->entry)))
		return (1);
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

void	handler_line(t_buf *cmd, t_read *info, t_key *entry)
{
	handler_buf(cmd, entry);

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
			handler_line(cmd, info, &entry);
		else if (ret == 1)
			break ;
	}
	ft_strdel(&cmd->cmd);
	return (ret);
}

void	sh_prompt(t_read *info)
{
	static int first;

	if (first++)
		write(1, "\n\r", 2);
	ft_putstr(PROMPT);
	info->prompt = ft_strlen(PROMPT);
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