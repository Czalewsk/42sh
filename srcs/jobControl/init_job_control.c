/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:38:14 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 16:03:04 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_job			*g_first_job;
t_list			*g_job_order;
t_process		*g_current_execute;
pid_t			g_shell_pgid;
int				g_shell_terminal;
int				g_shell_is_interactive;

void	init_job_control(void)
{
	const	struct sigaction	action = {.sa_handler = SIG_IGN};

	g_shell_terminal = STDIN_FILENO;
	g_shell_is_interactive = isatty(g_shell_terminal);
	if (!g_shell_is_interactive)
		exit(sh_error(1, 0, NULL, 1,
			"Merci de lancer le shell dans une fenetre interactive\n"));
	while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
		kill(-g_shell_pgid, SIGTTIN);
	signal_handler_init();
	sigaction(SIGTTOU, &action, NULL);
	g_shell_pgid = getpid();
	if (setpgid(g_shell_pgid, g_shell_pgid) < 0)
		exit(sh_error(1, 0, NULL, 1,
			"Impossible de mettre le shell \
				dans sont propre groupe de process\n"));
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
}
