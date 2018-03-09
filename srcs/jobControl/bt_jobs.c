/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:37:27 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/09 18:36:22 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int        jobs_usage(char c)
{
    char tmp[2];

    tmp[0] = c;
    tmp[1] = 0;
    sh_error(0, 0, NULL, 3, "jobs: -", tmp, ": invalid option\n");
    return (sh_error(1, 0, NULL, 1, "jobs: usage: jobs [-lprs] [jobspec]\n"));
}

static int  jobs_display_jobspec(char info, char run_or_stop, char **arg)
{
    int     i;
    int     retour;
    t_job   *tmp;

    i = 0;
    retour = 0;
    while (arg[i] != NULL)
    {
        tmp = get_job(arg[i]);
        if (tmp == NULL)
            retour = sh_error(1, 0, NULL, 3, "jobs: ", arg[i], ": no such job\n");
        else if (run_or_stop == 'r' && (job_is_stopped(tmp) || job_is_completed(tmp)))
            ;
        else if (run_or_stop == 's' && !job_is_stopped(tmp))
            ;
        else if (info == 'p')
            jobs_display_only_id(tmp);
        else if (info == 'l')
            jobs_display(tmp, 1);
        else
            jobs_display(tmp, 0);
        i++;
    }
    return (retour);
}

static int  jobs_display_no_jobspec(char info, char run_or_stop)
{
    t_job       *j;
    t_job       *next;

    j = first_job;
    while (j != NULL)
    {
        next = j->next;
        if (run_or_stop == 'r' && (job_is_stopped(j) == 0 || job_is_completed(j) == 0))
            ;
        else if (run_or_stop == 's' && job_is_stopped(j) != 0)
            ;
        else if (info == 'p')
            jobs_display_only_id(j);
        else if (info == 'l')
            jobs_display(j, 1);
        else
            jobs_display(j, 0);
        j = next;
    }
    return (0);
}


int         bt_jobs(char **arg)
{
    char    info;
    char    run_or_stop;
    int     i;
    int     j;
    
    i = 0;
    info = 0;
    run_or_stop = 0;
    while (arg[i])
    {
        if (arg[i][0] != '-')
            break ;
        j = 1;
        while (arg[i][j])
        {
            if (arg[i][j] == 'l' || arg[i][j] == 'p')
                info = arg[i][j];
            else if (arg[i][j] == 'r' || arg[i][j] == 's')
                run_or_stop = arg[i][j];
            else
                return (jobs_usage(arg[i][j]));
            j++;
        }
        i++;    
    }
    if (arg == NULL || arg[i] == NULL)
        jobs_display_no_jobspec(info, run_or_stop);
    else
        jobs_display_jobspec(info, run_or_stop, arg);
    clear_completed_job();
    return (0);
}