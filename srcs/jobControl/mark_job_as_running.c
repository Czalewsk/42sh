/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_job_as_running.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:40:00 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 16:27:07 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/* Mark a stopped job J as being running again.  */

void mark_job_as_running (t_job *j)
{
  t_process *p;

  p = j->process;
  p->stopped = 0;
  // while (p)
  // {
  //     p->stopped = 0;
  //     p = p->next;
  // }
  j->notified = 0;
}
