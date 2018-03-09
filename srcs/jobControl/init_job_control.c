/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:38:14 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/09 15:11:14 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	init_job_control(void)
{
	const	struct sigaction	action = {.sa_handler = SIG_IGN};

	shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty(shell_terminal);
	if (!shell_is_interactive)
		exit (sh_error(1, 0, NULL, 1,	"Merci de lancer le shell dans une fenetre interactive\n"));
	while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
		kill(- shell_pgid, SIGTTIN);
	signal_handler_init();
	sigaction(SIGTTOU, &action, NULL);
	shell_pgid = getpid();
	if (setpgid(shell_pgid, shell_pgid) < 0)
		exit (sh_error(1, 0, NULL, 1, "Impossible de mettre le shell dans sont propre groupe de process\n"));
	tcsetpgrp(shell_terminal, shell_pgid);
}