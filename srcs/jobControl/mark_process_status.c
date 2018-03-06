/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_process_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:31:22 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/04 19:00:16 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/* Store the status of the process pid that was returned by waitpid.
   Return 0 if all went well, nonzero otherwise.  */

//    int mark_process_status (pid_t pid, int status)
//    {
//      t_job *j;
//      t_process *p;
   
//      if (pid > 0)
//        {
//          /* Update the record for the process.  */
//          for (j = first_job; j; j = j->next)
//            for (p = j->first_process; p; p = p->next)
//              if (p->pid == pid)
//                {
//                  p->status = status;
//                  if (WIFSTOPPED (status))
//                    p->stopped = 1;
//                  else
//                    {
//                      p->completed = 1;
//                      if (WIFSIGNALED (status))
//                        fprintf (stderr, "%d: Terminated by signal %d.\n",
//                                 (int) pid, WTERMSIG (p->status));
//                    }
//                  return 0;
//                 }
//          fprintf (stderr, "No child process %d.\n", pid);
//          return -1;
//        }
//      else if (pid == 0 || errno == ECHILD)
//        /* No processes ready to report.  */
//        return -1;
//      else {
//        /* Other weird errors.  */
//        perror ("waitpid");
//        return -1;
//      }
//    }
   

int mark_process_status (pid_t pid, int status)
{
	t_job		*tmp;
	t_process	*p;
	
	if (pid == 0)
		return -1;
	else if (pid < 0)
		return (sh_error(1, 0, NULL, 1, "job control: waitpid"));
	tmp = first_job;
	while (tmp)
	{
		p = tmp->process;
		if (p->pid == pid)
		{
			p->status = status;
			if (WIFSTOPPED (status))
			{
				DEBUG("mark_process_status ligne 75 : process %d est stop\n", p->pid);
				p->stopped = 1;
			}
			else
			{
				DEBUG("mark_process_status ligne 80 : process %d est fini\n", p->pid);
				p->completed = 1;
				/*
				if (WIFSIGNALED (status))
				fprintf (stderr, "%d: Terminated by signal %d.\n",
							(int) pid, WTERMSIG (p->status));
				*/
			}
			return 0;
		}
		tmp = tmp->next;
	}
	return -1;
}