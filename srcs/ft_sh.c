/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/28 08:43:43 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			g_edition_state = 0;

inline void	info_init(t_read *info)
{
	struct winsize	ws;

	ft_bzero(info, sizeof(t_read));
	ioctl(1, TIOCGWINSZ, &ws) ? ft_bzero(&ws, sizeof(ws)) : 0;
	info->win_co = ws.ws_col;
}

int			main(int ac, char **av, char **env)
{
	t_buf		cmd;
	t_read		info;
	char		ret;

	ret = 0;
	termcaps_init(env);
	while (ac || av)
	{
		info_init(&info);
		prompt_display(&info);
		if ((ret = read_line(&cmd, &info)) < 0)
			break ;
		DEBUG("\r\nCMD=|%s|", cmd.cmd);
		/*  TEST ADD PROMPT */
		char *line = NULL;
		char ret2 = 0;
		if (!ft_strcmp(cmd.cmd, "testprompt"))
		{
			while (42)
			{
			ret2 = prompt_add("test add prompt > ", &line);
			DEBUG("\t(%d)LINE=~%s~\n", ret, line)
				if (ret2 < 0 || !ft_strcmp("stop", line))
					break ;
			}
		}
		/*  FIN DU TEST     */
		ft_strdel(&cmd.cmd);
	}
	ft_strdel(&cmd.cmd);
	termcaps_restore_tty();
	return (ret);
}
