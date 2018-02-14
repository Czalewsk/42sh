/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:49:28 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/10 16:51:26 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		cpy_to_normal(t_buf *cmd, t_read *info, t_key *entry)
{
	g_sh.edition_state = NORMAL;
	(void)entry;
	cursor_back_home(info);
	write(g_sh.fd_tty, cmd->cmd, cmd->size_actual);
	cursor_display_update(info, 1);
	return (key_manager(cmd, info, entry));
}
