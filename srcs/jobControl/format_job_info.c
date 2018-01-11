/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_job_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:33:28 by scorbion          #+#    #+#             */
/*   Updated: 2017/12/03 16:45:24 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

/* Format information about job status for the user to look at.  */

void  format_job_info (t_job *j, const char *status)
{
  fprintf (stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}