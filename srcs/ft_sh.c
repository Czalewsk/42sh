/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:49:09 by bviala            #+#    #+#             */
/*   Updated: 2017/11/28 08:49:02 by czalewsk         ###   ########.fr       */
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
		ft_strdel(&cmd.cmd);
	}
	ft_strdel(&cmd.cmd);
	termcaps_restore_tty();
	return (ret);
}
