/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/08 17:06:37 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_sh		g_sh;

inline void	info_init(t_read *info)
{
	struct winsize	ws;

	ft_bzero(info, sizeof(t_read));
	ioctl(1, TIOCGWINSZ, &ws) ? ft_bzero(&ws, sizeof(ws)) : 0;
	info->win_co = ws.ws_col;
}

static void	sh_init_prog(char **env)
{
	int i;
	int j;

	g_sh.edition_state = 0;
	g_sh.hist = ft_ldl_new_list();
	g_sh.hist_current = NULL;
	g_sh.hist_i = 0;
	g_sh.hist_file = ft_strjoin(ft_getenv(env, "HOME"), "/");
	g_sh.hist_file = ft_strjoin_free(g_sh.hist_file, HIST_FILE, 0);
	j = 0;
	while (env && env[j])
		j++;
	g_sh.env = (char **)ft_memalloc(sizeof(char *) * (j + 1));
	i = 0;
	while (*env)
	{
		g_sh.env[i] = ft_strdup(*env);
		i++;
		env++;
	}
	g_sh.env[i] = NULL;
	termcaps_init(g_sh.env);
}

int			main(int ac, char **av, char **env)
{
	t_buf		cmd;
	t_read		info;
	char		ret;

	ret = 0;
	sh_init_prog(env);
	while (ac || av)
	{
		info_init(&info);
		prompt_display(&info);
		if ((ret = read_line(&cmd, &info)) == -1)
			break ;
		if (ret == -3)
			continue ;
		DEBUG("\r\nCMD=|%s|", cmd.cmd);
		ft_strdel(&cmd.cmd);
	}
	ft_strdel(&cmd.cmd);
	termcaps_restore_tty();
	return (ret);
}
