/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/27 14:23:35 by czalewsk         ###   ########.fr       */
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
char		g_sh_exit;

inline void	info_init(t_read *info)
{
	struct winsize	ws;

	ft_bzero(info, sizeof(t_read));
	g_sh.prompt_add = 0;
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
	cwd_destroy();
	env_destroy();
	ft_strdel(&cmd->cmd);
	ft_strdel(&g_sh.pasted);
	termcaps_restore_tty();
	close(g_sh.fd_tty);
	close(g_sh.test_fd);
	close(g_sh.fds[0]);
	close(g_sh.fds[1]);
	close(g_sh.fds[2]);
	clear_job();
}

static void	sh_init_prog(char **env, t_buf *cmd, t_read *info)
{
	tputs(tgetstr("rs", NULL), 0, &ft_putchar_termcap);
	init_job_control();
	ft_bzero(&g_sh, sizeof(t_sh));
	g_termcps_fd = g_sh.fd_tty;
	env_init((const char **)env);
	cwd_init();
	g_sh.hist_file = ft_strjoin(ft_getenv(env, "HOME"), "/");
	g_sh.hist_file = ft_strjoin_free(g_sh.hist_file, HIST_FILE, 0);
	init_fd();
	g_termcps_fd = g_sh.fd_tty;
	init_history();
	termcaps_init();
	update_display_init(info, cmd);
}

inline void	sh_reinit_edition_state(t_buf *cmd, t_read *info, t_key *entry)
{
	if (g_special_case[g_sh.edition_state])
		g_special_case[g_sh.edition_state](cmd, info, entry);
}


void		printtoken(char **cmd)
{
	t_token	tk;
	t_token	*tk2;
	char	*cur;
	t_list	*lst;
	t_list	*prev;

	cur = *cmd;
	while (lexer_getnexttoken(&tk, &cur, cmd) > 0)
	{
		ft_printf("TOKEN: %s | Size: %zu | Class: %i\n",
tk.str, tk.size, tk.id);
		if (expansions_expand(&lst, &tk))
		{
			ft_printf("\t--EXPAND--\n");
			while (lst)
			{
				tk2 = (t_token *)lst->content;
				ft_printf("\tExpand: %s | Size: %zu | Class: %i\n", tk2->str,
						tk2->size, tk2->id);
				prev = lst;
				lst = lst->next;
				free(tk2->str);
				free(tk2);
				free(prev);
			}
		}
		free(tk.str);
	}
}


int			main(int ac, char **av, char **env)
{
	t_buf		cmd;
	t_read		info;
	char		ret;

	ret = 0;
	sh_init_prog(env, &cmd, &info);
	while (!g_sh_exit && (ac || av))
	{
		sh_reinit_edition_state(&cmd, &info, NULL);
		info_init(&info);
		prompt_display(&info, g_new_prompt);
		buff_max_char_init(&info);
		if ((ret = read_line(&cmd, &info)) == -1)
			break ;
		update_status();
		if (ret != -3)
			//printtoken(&cmd.cmd);
			parser(&cmd.cmd);
		do_job_notification();
		ft_strdel(&cmd.cmd);
	}
	sh_quit_prog(&cmd);
	return (g_sh.exitstatus);
}
