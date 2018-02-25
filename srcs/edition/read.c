/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:53:46 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/20 18:49:21 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char			(*const g_special_case[EDITION_MAX_STATE])
		(t_buf *cmd, t_read *info, t_key *entry) = {
	NULL, &completion_to_normal_char, &history_to_normal_char,
	&pasted_remove_highlight_char, &pasted_remove_highlight_char
};

void			read_key(t_key *entry)
{
	int		ret;

	ret = read(g_sh.test_fd, entry->entry + entry->nread, SIZE_READ);
	if (ret == -1)
		ft_error(strerror(errno), &termcaps_restore_tty); // A recoder :D
	entry->nread += ret;
}

void			debug_key(t_key *entry)
{
	int		i;

	i = 0;
	DEBUG("READ=%i\r\n", entry->nread);
	while (i < entry->nread)
		DEBUG("%hhi\r\n", entry->entry[i++]);
}

/*
** Retourne un char dans read_line
** 0 -> copier coller donc la ligne nest pas finie
** -1 -> retourne la ligne
** pas dautres idees pour le moments...
*/

char			key_wrapper(t_buf *cmd, t_read *info, t_key *entry)
{
//	debug_key(entry);
	if ((entry->entry[0] == 27 || ft_iswcntrl((int)*(entry->entry))))
		return (key_manager(cmd, info, entry));
	else
	{
		if (g_special_case[g_sh.edition_state])
			g_special_case[g_sh.edition_state](cmd, info, entry);
		return (insert_char(cmd, info, entry));
	}
}

char			read_line(t_buf *cmd, t_read *info)
{
	t_key		entry;
	char		ret;

	buff_handler(cmd, NULL, NULL, info);
	ft_bzero(&entry, sizeof(t_key));
	while (42)
	{
		read_key(&entry);
		ret = key_wrapper(cmd, info, &entry);
		if (ret < 0)
			break ;
	}
	return (ret);
}
