/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/09 19:03:18 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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
		if (!(ret = read_line(&cmd, &info)))
			break ;
		DEBUG("\r\nCMD=|%s|", cmd.cmd)
		ft_strdel(&cmd.cmd);
	}
	termcaps_restore_tty();
	return (ret);
}