/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 04:42:37 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/06 14:17:50 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		insert_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char	*curs;
	int		len;

	if (!buff_handler(cmd, entry, NULL, info))
		return (1);
	cmd->size_actual += entry->nread;
	if (info->curs_char == (long)info->total_char)
	{
		ft_strncat(cmd->cmd, entry->entry, entry->nread);
		write(g_sh.fd_tty, entry->entry, entry->nread);
	}
	else
	{
		len = sh_curs_unicode(cmd->cmd, info->curs_char, 0);
		(curs = cmd->cmd + len) && ft_memmove(curs + entry->nread, curs,
				sh_curs_unicode(cmd->cmd, ft_strlen(curs) + 1, 1));
		ft_memcpy(curs, entry->entry, entry->nread);
		cursor_back_home(info, 1);
		write(g_sh.fd_tty, cmd->cmd, cmd->size_actual);
	}
	len = ft_strlen_utf8(entry->entry);
	(info->curs_char += len) && (info->total_char += len);
	cursor_display_update(info, 1);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}

char		delete_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char		*curs;

	(void)entry;
	if (!cmd->cmd || !info->curs_char)
		return (0);
	curs = cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char, 1);
	ft_memmove(cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char - 1, 0),
			curs, ft_strlen(curs) + 1);
	cursor_back_home(info, 1);
	cmd->size_actual = ft_strlen(cmd->cmd);
	write(g_sh.fd_tty, cmd->cmd, cmd->size_actual);
	info->curs_char--;
	info->total_char = ft_strlen_utf8(cmd->cmd);
	cursor_display_update(info, 1);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}

char		suppr_char(t_buf *cmd, t_read *info, t_key *entry)
{
	char		*curs;

	(void)entry;
	if (!cmd->cmd || (long)info->total_char == info->curs_char)
		return (0);
	curs = cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char, 0);
	ft_memmove(curs, cmd->cmd + sh_curs_unicode(cmd->cmd,
				info->curs_char + 1, 1), ft_strlen(curs) + 1);
	cmd->size_actual = ft_strlen(cmd->cmd);
	cursor_back_home(info, 1);
	write(g_sh.fd_tty, cmd->cmd, cmd->size_actual);
	info->total_char--;
	cursor_display_update(info, 1);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}
