/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:32:04 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/08 21:26:09 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	debug_key(char key[SIZE_READ], int nb, long *nbr)
{
	int i;
	int fd;

	i = 0;
	fd = open(DEBUG_WINDOW, O_RDWR);
	dprintf(fd, "READ=%i long=%ld\r\n", nb, *nbr);
	while (i < nb)
		dprintf(fd, "%hhi\r\n", key[i++]);
	close(fd);
}


static char		is_delete(int nread, long int value)
{
	if ((nread == 1 && value == 127) || (nread == 4 && value == DEL_KEY))
		return (1);
	else
		return (0);
}

static char	key_wrapper(t_key *entry, t_read *info)
{
	(void)info;
	if (entry->nread == 1 && *(entry->entry) == 13)
		return (1);
//	else if (entry->nread == 3 && entry->entry[0] == 27 && entry->entry[1] == 91)
//		arrow_handler(entry->entry[2], info);
	return (2);
}

static void			read_key(t_key *entry)
{
	while ((entry->nread = read(0, entry->entry, SIZE_READ))  <= 0)
		if (entry->nread == -1)
			ft_error(strerror(errno), &termcaps_restore_tty); // A recoder :D
}

static char		read_entry(t_read *info, t_key *entry)
{
	read_key(entry);
	debug_key(entry->entry, entry->nread, (long*)(entry->entry));
	if (entry->nread == 1 && CTRL_KEY('d') == *(entry->entry))
		return (-1);
	if ((entry->nread <= (int)sizeof(wint_t) 
				&& !ft_iswcntrl((int)*(entry->entry)))
				|| is_delete(entry->nread, (long)*(entry->entry)))
		return (0);
	else
		return (key_wrapper(entry, info));
}

int				read_line(t_buf *cmd, t_read *info)
{
	char	ret;
	t_key	entry;

	ret = 0;
	ft_bzero(&entry, sizeof(t_key));
	buff_handler(cmd, NULL);
	while (42)
	{
		if ((ret = read_entry(info, &entry)) == -1)
			break ;
//		if (!ret)
//			line_wrapper(cmd, info, &entry);
		else if (ret == 1)
			break ;
	}
	return (ret);
}

