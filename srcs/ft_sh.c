/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:49:09 by bviala            #+#    #+#             */
/*   Updated: 2017/11/17 15:49:15 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			g_edition_state = 0;

static void	info_init(t_read *info)
{
	ft_bzero(info, sizeof(t_read));
	info->win_co = tgetnum("co");
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
