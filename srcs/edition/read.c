/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:53:46 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/24 09:31:30 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			debug_key(t_key *entry)
{
	int		i;

	i = 0;
	DEBUG("READ=%i\r\n", entry->nread);
	while (i < entry->nread)
		DEBUG("%hhi\r\n", entry->entry[i++]);
}

void			read_key(t_key *entry)
{
	int		ret;

	ret = read(0, entry->entry + entry->nread, SIZE_READ);
	if (ret == -1)
		ft_error(strerror(errno), &termcaps_restore_tty); // A recoder :D
	entry->nread += ret;
}

/*
** Retourne un char dans read_line
** 0 -> copier coller donc la ligne nest pas finie
** -1 -> retourne la ligne
** pas dautres idees pour le moments...
*/

char			key_wrapper(t_buf *cmd, t_read *info, t_key *entry)
{
	if ((entry->entry[0] == 27 || ft_iswcntrl((int)*(entry->entry))))
		return (key_manager(cmd, info, entry));
	else
		return (insert_char(cmd, info, entry));
}

char			read_line(t_buf *cmd, t_read *info)
{
	t_key		entry;
	char		ret;

	buff_handler(cmd, NULL);
	ft_bzero(&entry, sizeof(t_key));
	while (42)
	{
		read_key(&entry);
		ret = key_wrapper(cmd, info, &entry);
//			continue ;
		if (ret < 0)
			break ;
		debug_key(&entry);
	}
	return (ret == -1 ? -1 : 1);
}
