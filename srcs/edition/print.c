/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 17:34:58 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/26 18:11:54 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	print_string(char *str, t_buf *cmd, t_read *info)
{
	int		len;
	char	*curs;

	len = ft_strlen(str);
	buff_handler(cmd, NULL, str);
	cmd->size_actual += len;
	curs = cmd->cmd + sh_curs_unicode(cmd->cmd, info->curs_char, 0);
	ft_memmove(curs + len, curs, sh_curs_unicode(cmd->cmd,
				ft_strlen(curs) + 1, 1));
	ft_memcpy(curs, str, len);
	cursor_back_home(info);
	write(1, cmd->cmd, cmd->size_actual);
	len = ft_strlen_utf8(str);
	info->curs_char += len;
	info->total_char += len;
	cursor_display_update(info, 1);
}

char	test_print(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)entry;
	print_string("YO😃 LO", cmd, info);
	return (0);
}