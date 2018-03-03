/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:10:34 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/02 11:46:16 by czalewsk         ###   ########.fr       */
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
	ft_bzero(&g_sh, sizeof(t_sh));
	g_sh.fd_tty = open(ttyname(0), O_WRONLY);
	g_sh.test_fd = open(ttyname(0), O_RDONLY);
	g_termcps_fd = g_sh.fd_tty;
	g_sh.hist_file = ft_strjoin(ft_getenv(env, "HOME"), "/");
	g_sh.hist_file = ft_strjoin_free(g_sh.hist_file, HIST_FILE, 0);
	env_init((const char **)env);
	init_history();
	termcaps_init();
	signal_handler_init();
}

// void		printenv(void)
// {
// 	int	i;

// 	i = -1;
// 	ft_printf("-- PRINT ENV START --\n");
// 	while (g_sh.env[++i])
// 		ft_printf("%s\n", g_sh.env[i]->var);
// 	ft_printf("-- PRINT ENV END --\n");
// }

// void		debugtim(void)
// {
// 	//env_unset("HOME");
// 	//env_set("HOME", "/coucou/plop", ENV_LOCAL);
// 	//env_make(ENV_LOCAL | ENV_GLOBAL | ENV_TEMP);
// 	//env_settype("HOME", ENV_LOCAL);
// 	//env_make(ENV_LOCAL | ENV_GLOBAL | ENV_TEMP);

// 	//ft_printenv(env_make(ENV_LOCAL));
// 	//ft_printf("FIRST IFS: '%s'\n", env_get("IFS"));
// }

// void		printtoken(char **cmd)
// {
// 	t_token	tk;
// 	t_token	*tk2;
// 	char	*cur;
// 	t_list	*lst;
// 	t_list	*prev;

// 	cur = *cmd;
// 	while (lexer_getnexttoken(&tk, &cur, cmd) > 0)
// 	{
// 		ft_printf("TOKEN: %s | Size: %zu | Class: %i\n", tk.str, tk.size, tk.id);
// 		if (expansions_expand(&lst, &tk))
// 		{
// 			ft_printf("\t--EXPAND--\n");
// 			while (lst)
// 			{
// 				tk2 = (t_token *)lst->content;
// 				ft_printf("\tExpand: %s | Size: %zu | Class: %i\n", tk2->str,
// 					tk2->size, tk2->id);
// 				prev = lst;
// 				lst = lst->next;
// 				free(tk2->str);
// 				free(tk2);
// 				free(prev);
// 			}
// 		}
// 		free(tk.str);
// 	}
// // =======
// // 	while (env && env[j])
// // 		j++;
// // 	g_sh.env = (char **)ft_memalloc(sizeof(char *) * (j + 1));
// // 	j = 0;
// // 	while (*env)
// // 	{
// // 		g_sh.env[j] = ft_strdup(*env);
// // 		j++;
// // 		env++;
// // 	}
// // 	init_history();
// // 	termcaps_init(g_sh.env);
// // 	signal_handler_init();
// //>>>>>>> master
// }

int			main(int ac, char **av, char **env)
{
	t_buf		cmd;
	t_read		info;
	char		ret;
	//int			savefds[3];

	ret = 0;
	sh_init_prog(env);
	while (ac || av)
	{
		info_init(&info);
		prompt_display(&info, 0);
		buff_max_char_init(&info);
		if ((ret = read_line(&cmd, &info)) == -1)
			break ;
		if (ret == -3)
			continue ;
		//savefds[0] = dup(STDIN_FILENO);
		//savefds[1] = dup(STDOUT_FILENO);
		//savefds[2] = dup(STDERR_FILENO);
		//printtoken(&cmd.cmd);
		parser(&cmd.cmd);
		//dup2(savefds[0], STDIN_FILENO);
		//dup2(savefds[1], STDOUT_FILENO);
		//dup2(savefds[2], STDERR_FILENO);
		ft_strdel(&cmd.cmd);
	}
	sh_quit_prog(&cmd);
	return (ret);
}
