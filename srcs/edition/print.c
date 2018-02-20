/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 17:34:58 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/20 18:48:54 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	add_str(t_buf *cmd, t_read *info, char *str)
{
	int		len;
	char	*curs;

	if (!buff_handler(cmd, NULL, str, info))
		return ;
	len = ft_strlen(str);
	cmd->size_actual += len;
	curs = cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char, 0);
	ft_memmove(curs + len, curs, sh_curs_unicode(cmd->cmd,
				ft_strlen(curs) + 1, 1));
	ft_memcpy(curs, str, len);
	cursor_back_home(info, 1);
	write(g_sh.fd_tty, cmd->cmd, cmd->size_actual);
	len = ft_strlen_utf8(str);
	info->curs_char += len;
	info->total_char += len;
	cursor_display_update(info, 1);
}

void	display_str(t_buf *cmd, t_read *info, char *str, size_t pos_curs)
{
	size_t		len;

	if (!cmd || !info)
		return ;
	if (str)
	{
		if (!buff_handler(cmd, NULL, str, info))
			return ;
		ft_strcpy(cmd->cmd, str);
	}
	cmd->size_actual = ft_strlen(cmd->cmd);
	if (g_sh.prompt_display)
		cursor_back_home(info, 1);
	else
	{
		cursor_back_home(info, 0);
		prompt_display(info, 0);
	}
	write(g_sh.fd_tty, cmd->cmd, cmd->size_actual);
	len = ft_strlen_utf8(str ? str : cmd->cmd);
	info->curs_char = (pos_curs > len) ? len : pos_curs;
	info->total_char = len;
	cursor_display_update(info, 1);
}
