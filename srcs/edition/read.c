/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:53:46 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/11 19:09:47 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_sh.h"

void	debug_key(t_key *entry)
{
	int		i;

	i = 0;
	DEBUG("READ=%i\r\n", entry->nread)
	while (i < entry->nread)
		DEBUG("%hhi\r\n", entry->entry[i++])
}

void		read_key(t_key *entry)
{
	while ((entry->nread = read(0, entry->entry, SIZE_READ))  <= 0)
		if (entry->nread == -1)
			ft_error(strerror(errno), &termcaps_restore_tty); // A recoder :D
}

char			is_pasted(t_key *entry)
{
	if (entry->nread < 6)
		return (0);
	else if (entry->entry[0] == 27 && entry->entry[1] == 91
			&& entry->entry[2] == 50 && entry->entry[3] == 48
			&& entry->entry[4] == 48 && entry->entry[5] == 126)
		return (1);
	else
		return (0);
}

/*
** Retourne un char dans read_line
** 0 -> copier coller donc la ligne nest pas finie
** -1 -> retourne la ligne
** pas dautres idees pour le moments...
*/

char			key_wrapper(t_buf *cmd, t_read *info, t_key *entry)
{
	if (is_pasted(entry))
		return (paste_handler(cmd, info, entry));
	else if (!ft_iswcntrl((int)*(entry->entry)))
		return (insert_char(cmd, info, entry));
	else
		return (key_manager(cmd, info, entry));
}

char			read_line(t_buf *cmd, t_read *info)
{
	t_key		entry;
	char		ret;

	buff_handler(cmd, NULL);
	while (42)
	{
		ft_bzero(&entry, sizeof(t_key));
		read_key(&entry);
		if (!(ret = key_wrapper(cmd, info, &entry)))
			continue ;
		else if (ret < 0)
			break ;
		debug_key(&entry);
	}
	return (ret == -1 ? -1 : 1);
}
