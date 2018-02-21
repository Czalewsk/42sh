/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:17:27 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/21 17:59:18 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static size_t	g_max_char_visu;

static void		realloc_t_buf(t_buf *cmd)
{
	cmd->size_max *= 2;
	cmd->cmd = ft_memrealloc(cmd->cmd, cmd->size_actual, cmd->size_max);
}

void			buff_max_char_init(t_read *info)
{
	struct winsize	ws;

	ioctl(g_sh.fd_tty, TIOCGWINSZ, &ws) ? ft_bzero(&ws, sizeof(ws)) : 0;
	g_max_char_visu = (ws.ws_col * ws.ws_row) - info->prompt;
}

static char		sh_limits_char(t_key *entry, char *str, t_read *info)
{
	size_t		len_visu;

	len_visu = str ? info->total_char + ft_strlen_utf8(str)
		: info->total_char + 1;
	if (len_visu < g_max_char_visu)
		return (1);
	if (str)
	{
		*(str + g_max_char_visu - 1) = 0;
		return (1);
	}
	else if (entry)
		ft_bzero(entry, sizeof(t_key));
	return (0);
}

char			buff_handler(t_buf *cmd, t_key *entry, char *str, t_read *info)
{
	int		len;

	if ((entry || str) && !sh_limits_char(entry, str, info))
		return (0);
	if (entry)
		while (entry->nread + cmd->size_actual >= cmd->size_max - 1)
			realloc_t_buf(cmd);
	else if (str)
	{
		len = ft_strlen(str);
		while (len + cmd->size_actual >= cmd->size_max - 1)
			realloc_t_buf(cmd);
	}
	else
	{
		cmd->size_max = SIZE_BUF_CMD;
		cmd->size_actual = 0;
		cmd->cmd = ft_strnew(SIZE_BUF_CMD);
	}
	return (1);
}
