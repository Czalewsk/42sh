/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:53:46 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/19 17:41:26 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_signal.h"

char			read_key(t_key *entry)
{
	int		ret;
	char	*new_line;

	ret = read(g_sh.test_fd, entry->entry + entry->nread, SIZE_READ);
	if (ret == -1)
	{
		ft_bzero(entry, sizeof(t_key));
		if (errno != EINTR)
			exit(sh_error(EXIT_FAILURE, 1, &termcaps_restore_tty, 1,
						"Error in read\n"));
		return (-3);
	}
	else
	{
		entry->nread += ret;
		if (ret > 1)
			while ((new_line = ft_strnchr(entry->entry, '\n', entry->nread)))
			{
				ft_memmove(new_line, new_line + 1,
						entry->nread - (new_line - entry->entry));
				--entry->nread;
			}
	}
	return (1);
}

/*
**void			debug_key(t_key *entry)
**{
**	int		i;
**
**	i = 0;
**	DEBUG("READ=%i\r\n", entry->nread);
**	while (i < entry->nread)
**		DEBUG("%hhi\r\n", entry->entry[i++]);
**}
*/

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
	sh_reinit_edition_state(cmd, info, entry);
	return (insert_char(cmd, info, entry));
}

char			read_line(t_buf *cmd, t_read *info)
{
	t_key		entry;
	char		ret;

	buff_handler(cmd, NULL, NULL, info);
	ft_bzero(&entry, sizeof(t_key));
	while (42)
	{
		signal_manager();
		ret = read_key(&entry);
		if (g_new_prompt || ret < 0)
			break ;
		ret = key_wrapper(cmd, info, &entry);
		if (ret < 0)
			break ;
	}
	return (ret);
}
