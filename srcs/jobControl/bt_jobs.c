/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:37:27 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 09:40:27 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

void        jobs_usage(char c)
{
    //42sh: jobs: -c: invalid option
    //jobs: usage: jobs [-lprs] [jobspec]
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
            //retour = retour || 42sh: jobs: arg[i]: no such job
        else if (run_or_stop == 'r' && (job_is_stopped(j) || job_is_completed(j)))
            continue ;
        else if (run_or_stop == 's' && !job_is_stopped(j))
            continue ;
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
    t_job   *tmp;

    tmp = first_job;
    while (tmp != NULL)
    {
        if (run_or_stop == 'r' && (job_is_stopped(j) || job_is_completed(j)))
            continue ;
        if (run_or_stop == 's' && !job_is_stopped(j))
            continue ;
        else if (info == 'p')
            jobs_display_only_id(tmp);
        else if (info == 'l')
            jobs_display(tmp, 1);
        else
            jobs_display(tmp, 0);
        tmp = tmp->next;
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
            {
                jobs_usage(arg[i][j]);
                return (1);
            }
            j++;
        }
        i++;    
    }
    if (arg[i] == NULL)
        jobs_display_no_jobspec(info, run_or_stop);
    else
        jobs_display_jobspec(info, run_or_stop);
    return (0);
}