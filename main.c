/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:00:06 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/02 19:23:51 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:00:06 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/02 19:00:06 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:10:44 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/02 18:57:10 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:10:44 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/02 17:10:44 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:09:56 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/02 17:09:56 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:32:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/02 17:09:40 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cedychou.h"

char	*left_cap = NULL;
char	*right_cap = NULL;

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
	left_cap = tgetstr("le", NULL);
	right_cap = tgetstr("nd", NULL);
	if (!left_cap || !right_cap)
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
**  Gere l'affichage et le deplacement du cursor (retour a la ligne...)
*/

void	sh_print_char(t_key *entry, t_read *info)
{
	write(1, entry->entry, entry->nread);
	info->total_char++;
	info->curs_co++;
}

/*
** Gere les differentes combinaisons de touches avec CONTROL
*/

char	cntrl_handler(int nread, char entry[SIZE_READ])
{
	return (0);
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
	if (entry->nread == 3 && entry->entry[0] == 27 && entry->entry[1] == 91)
		arrow_handler(entry->entry[2], info);
	return (0);
}

char	read_entry(t_key *entry, t_read *info)
{
	read_key(entry);
	if (entry->nread == 1 && CTRL_KEY('a') == *(entry->entry))
		return (1);
	if (entry->nread <= sizeof(wint_t) && !ft_iswcntrl((int)*(entry->entry)))
		sh_print_char(entry, info);
	else
		return (key_wrapper(entry, info)); // Switch entre les differents gestionnaires de touches
	return (0);
}

unsigned char	read_line(char **cmd, t_read *info)
{
	unsigned char	ret;
	size_t			size_max;
	size_t			size_actual;
	t_key			entry;

	ret = 0;
	ft_bzero(&entry, sizeof(t_key));
	size_max = 128;
	size_actual = 0;
	*cmd = ft_strnew(size_max);
	while (42)
	{
		if ((ret = read_entry(&entry, info)))
			break ;
		if (entry.nread == 1 && *(entry.entry) == 13)
			break ;
		if (entry.nread + size_actual >= size_max - 1)
		{
			size_max *= 2;
			*cmd = ft_memrealloc(*cmd, size_actual, size_max);
		}
		*cmd = ft_strncat(*cmd, entry.entry, entry.nread);
		size_actual += entry.nread;
	}
	if (ret)
		ft_strdel(cmd);
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
	info->co = tgetnum("co");
	info->li = tgetnum("li");
}

int		main(void)
{
	char			*cmd;
	unsigned char	ret;
	t_read			info;

	cmd = NULL;
	set_tty();
	if (!init_termcap())
		return (1);
	while (42)
	{
		init_info(&info);
		sh_prompt(&info); // Envoyer la valeur de ret et include dans la boucle
		// A remplacer par une fonction qui return uniquement quand elle recoit un \n
		if ((ret = read_line(&cmd, &info)))
			break ;
		ft_printf("|%s|", cmd);
		ft_strdel(&cmd);
		// Execute a ret = cmd(&cmd);
	}
	restore_tty_param();
}
