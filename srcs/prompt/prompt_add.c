/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:10:44 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/27 14:56:08 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*prompt_add(char *prompt)
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
	while (42)
	{
		if ((ret = read_line(&cmd, &info)) < 0)
			break ;
		DEBUG("rturn=%d\n", ret)
	}
	return (cmd.cmd);
}

char	test_prompt_add(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)cmd;
	(void)info;
	(void)entry;
	DEBUG("TEST_PROMPT~%s~\n", prompt_add("test xD > "));
	return (-1);
}