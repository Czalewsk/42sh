/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:56:19 by scorbion          #+#    #+#             */
/*   Updated: 2018/01/20 18:19:35 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char *tab1[4] = {"/bin/ls", "-lR", "/"};
t_list  *jobs;

t_job       *create_t_job()
{
    t_job   *new;

    new = (t_job*)ft_memalloc(sizeof(t_job));
    new->command = NULL;
	new->first_process = NULL;
	new->pgid = 0;
    new->notified = 0;
    return (new);
}

t_process   *create_t_process()
{
    t_process   *new;

    new = (t_process*)ft_memalloc(sizeof(t_process));
	new->argv = tab1;
	new->pid = 0;
	new->completed = 0;
	new->stopped = 0;
	new->status = 0;
	new->stdin = 0;
	new->stdout = 1;
    new->stderr = 2;
    return (new);
}

int main(void)
{
    t_job   *j;
    t_process *p;

    j = create_t_job();
    p = create_t_process();
    ft_lstaddback(&(j->first_process), ft_lstnew(p, sizeof(t_process)));
    free(p);
    

    return (0);
}