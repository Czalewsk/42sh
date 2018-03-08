/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:26:09 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/08 11:42:42 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// void launch_process (t_process *p, pid_t pgid, int foreground, char **env)
// {
//   pid_t pid;

//   if (shell_is_interactive)
//     {
//       /* Put the process into the process group and give the process group
//          the terminal, if appropriate.
//          This has to be done both by the shell and in the individual
//          child processes because of potential race conditions.  */
//       pid = getpid ();
//       if (pgid == 0)
//         pgid = pid;
//       setpgid (pid, pgid);
//       if (foreground)
//       {
//         if (tcsetpgrp (shell_terminal, pgid) == -1)
//         {
//           perror("tcsetgprp");
//           exit(1);
//         }
//       }
//       /* Set the handling for job control signals back to the default.  */
//       signal (SIGINT, SIG_DFL);
//       signal (SIGQUIT, SIG_DFL);
//       signal (SIGTSTP, SIG_DFL);
//       signal (SIGTTIN, SIG_DFL);
//       signal (SIGTTOU, SIG_DFL);
//       signal (SIGCHLD, SIG_DFL);
//     }
//   /* Set the standard input/output channels of the new process.  */
//   if (p->stdin != STDIN_FILENO)
//     {
//       dup2 (p->stdin, STDIN_FILENO);
//       close (p->stdin);
//     }
//   if (p->stdout != STDOUT_FILENO)
//     {
//       dup2 (p->stdout, STDOUT_FILENO);
//       close (p->stdout);
//     }
//   if (p->stderr != STDERR_FILENO)
//     {
//       dup2 (p->stderr, STDERR_FILENO);
//       close (p->stderr);
//     }

//   /* Exec the new process.  Make sure we exit.  */
//   execve (p->argv[0], p->argv, env);
//   perror ("execve");
//   exit (1);
// }

void  launch_process(char *tmp, t_process *p, t_job *j, char **env)
{
	pid_t	pid;
	pid_t	pgid;

	if (shell_is_interactive)
	{
/*
		
		//signal(SIGTTOU, NULL);
		*/
		DEBUG("avant le bordel\n");
		pid = getpid();
		if (j && j->pgid == 0)
			j->pgid = pid;
		else
			pgid = pid;
		setpgid(pid, j ? j->pgid : pgid);
		DEBUG("avant le tcsetpgrp\n");
		if (!j)
		{
			// if (tcsetpgrp(shell_terminal, pgid) == -1)
			// {
			// 	//perror("tcsetpgrp");
			// 	//exit(sh_error(1, 0, NULL, 1, "Erreur tcsetpgrp launch_process\n"));
			// }
			// sleep(1);
			// DEBUG("FILS Mon groupe : %d\n", getpgid(getpid()));
			// DEBUG("avant le tcsetpgrp le terminal appartient au groupe : %d\n", tcgetpgrp(shell_terminal));
			// DEBUG("retour de tcsetpgrp %d\n", tcsetpgrp(STDIN_FILENO, getpgid(getpid())));
			// DEBUG("apres le tcsetpgrp le terminal appartient au groupe : %d\n", tcgetpgrp(shell_terminal));
		}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		DEBUG("apres le tcsetpgrp\n");
	}
	exit(g_sh.exitstatus = execve(tmp, p->argv, env));
}
