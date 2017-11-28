/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:10:44 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/28 08:33:21 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	prompt_add(char *prompt, char **line)
{
	t_buf		cmd;
	t_read		info;
	char		ret;

	ret = 0;
	info_init(&info);
	info.prompt = ft_strlen_utf8(prompt);
	buff_handler(&cmd, NULL, NULL);
	write(1, "\n\r", 2);
	ft_putstr(prompt);
	ret = read_line(&cmd, &info);
	*line = cmd.cmd;
	return (ret);
}