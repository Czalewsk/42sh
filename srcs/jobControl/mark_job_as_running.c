/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_job_as_running.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:40:00 by scorbion          #+#    #+#             */
/*   Updated: 2017/12/03 17:20:12 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

/* Mark a stopped job J as being running again.  */

void mark_job_as_running (t_job *j)
{
  t_process *p;

  p = j->first_process;
  while (p)
  {
      p->stopped = 0;
      p = p->next;
  }
  j->notified = 0;
}
