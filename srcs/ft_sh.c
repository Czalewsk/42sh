/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/10 17:09:57 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "lexer.h"
#include "expansions.h"
#include "sh_signal.h"

t_sh		g_sh;

inline void	info_init(t_read *info)
{
	struct winsize	ws;

	g_sh.fd_tty = open(ttyname(0), O_WRONLY);
	g_sh.test_fd = open(ttyname(0), O_RDONLY);
	//g_sh.prompt_display = 0;
	ft_bzero(info, sizeof(t_read));
	ioctl(g_sh.fd_tty, TIOCGWINSZ, &ws) ? ft_bzero(&ws, sizeof(ws)) : 0;
	info->win_co = ws.ws_col;
	info->win_height = ws.ws_row - 1;
}

static void	sh_quit_prog(t_buf *cmd)
{
	ft_ldl_clear(&g_sh.hist, &ft_strdel);
	ft_ldl_clear(&g_sh.history, &ft_strdel);
	ft_strdel(&(g_sh.hist_file));
	ft_strdel(&(g_sh.h_save));
	env_destroy();
	ft_strdel(&cmd->cmd);
	ft_strdel(&g_sh.pasted);
	termcaps_restore_tty();
}

static void	sh_init_prog(char **env)
{
	init_job_control();
	ft_bzero(&g_sh, sizeof(t_sh));
	g_termcps_fd = g_sh.fd_tty;
	g_sh.hist_file = ft_strjoin(ft_getenv(env, "HOME"), "/");
	g_sh.hist_file = ft_strjoin_free(g_sh.hist_file, HIST_FILE, 0);
	init_history();
	env_init((const char **)env);
	termcaps_init();
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
		prompt_display(&info, g_new_prompt);
		buff_max_char_init(&info);
		if ((ret = read_line(&cmd, &info)) == -1)
			break ;
		if (ret == -3)
			continue ;
		do_job_notification();
		parser(&cmd.cmd);
		//do_job_notification();
		ft_strdel(&cmd.cmd);
	}
	sh_quit_prog(&cmd);
	return (ret);
}
