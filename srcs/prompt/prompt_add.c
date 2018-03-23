/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:10:44 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/19 18:10:01 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	prompt_add(char *prompt, char **line, int i)
{
	t_buf		cmd;
	t_read		info;
	char		ret;

	ret = 0;
	info_init(&info);
	info.prompt = ft_strlen_utf8(prompt);
	if (i == 0)
		write(g_sh.fd_tty, "\n\r", 2);
	ft_putstr_fd(prompt, g_sh.fd_tty);
	g_sh.prompt_add = 1;
	ret = read_line(&cmd, &info);
	*line = cmd.cmd;
	return (ret);
}
