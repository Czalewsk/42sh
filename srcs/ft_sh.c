/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/07 19:37:26 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "lexer.h"
#include "expansions.h"
#include "sh_signal.h"

char			(*const g_special_case[EDITION_MAX_STATE])
		(t_buf *cmd, t_read *info, t_key *entry) = {
	NULL, &completion_to_normal_char, &history_to_normal_char,
	&pasted_remove_highlight_char, &pasted_remove_highlight_char
};

t_sh		g_sh;

inline void	info_init(t_read *info)
{
	struct winsize	ws;

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
	close(g_sh.fd_tty);
	close(g_sh.test_fd);
}

static void	sh_init_prog(char **env)
{
	ft_bzero(&g_sh, sizeof(t_sh));
	g_termcps_fd = g_sh.fd_tty;
	g_sh.hist_file = ft_strjoin(ft_getenv(env, "HOME"), "/");
	g_sh.hist_file = ft_strjoin_free(g_sh.hist_file, HIST_FILE, 0);
	env_init((const char **)env);
	g_sh.fd_tty = open(ttyname(0), O_WRONLY);
	g_sh.test_fd = open(ttyname(0), O_RDONLY);
	g_termcps_fd = g_sh.fd_tty;
	init_history();
	termcaps_init();
	signal_handler_init();
}

inline void	sh_reinit_edition_state(t_buf *cmd, t_read *info, t_key *entry)
{
	if (g_special_case[g_sh.edition_state])
		g_special_case[g_sh.edition_state](cmd, info, entry);
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
		sh_reinit_edition_state(&cmd, &info, NULL);
		info_init(&info);
		prompt_display(&info, g_new_prompt);
		buff_max_char_init(&info);
		g_sh.fds[0] = dup(STDIN_FILENO);
		g_sh.fds[1] = dup(STDOUT_FILENO);
		g_sh.fds[2] = dup(STDERR_FILENO);
		if ((ret = read_line(&cmd, &info)) == -1)
			break ;
		if (ret != -3)
			parser(&cmd.cmd);
		do_job_notification();
		ft_strdel(&cmd.cmd);
	}
	sh_quit_prog(&cmd);
	return (ret);
}
