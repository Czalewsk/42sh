/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:56:19 by scorbion          #+#    #+#             */
/*   Updated: 2018/01/23 15:45:53 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/job_control.h"

char *tab1[4] = {"/bin/ls", "-lR", "."};

int shell_terminal;
int shell_is_interactive;
int shell_pgid;


int main(int argc, char **argv, char **env)
{
    t_process *p;

    shell_terminal = STDIN_FILENO;
    shell_is_interactive = isatty (shell_terminal);

    signal (SIGINT, SIG_IGN);
    signal (SIGQUIT, SIG_IGN);
    signal (SIGTSTP, SIG_IGN);
    signal (SIGTTIN, SIG_IGN);
    signal (SIGTTOU, SIG_IGN);
    signal (SIGCHLD, SIG_IGN);
     int pid;
    if ((pid = fork()) == 0)
    {
        p = (t_process*)malloc(sizeof(t_process));
        p->next = NULL;
        p->argv = tab1;
        p->completed = 0;
        p->stopped = 0;
        p->status = 0;
        p->stdin = STDIN_FILENO;
        p->stdout = STDOUT_FILENO;
        p->stderr = STDERR_FILENO;
        p->pid = getpid();
        launch_process (p, 0, 1, env);
    }
    
    return (0);
}