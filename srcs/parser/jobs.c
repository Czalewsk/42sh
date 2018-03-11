/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:49:17 by maastie           #+#    #+#             */
/*   Updated: 2018/03/11 14:40:24 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*get_command_from_process(char **argv_p)
{
	int		i;
	int		e;
	char	*ret;

	i = 0;
	e = 0;
	while (argv_p && argv_p[i])
		e = e + ft_strlen(argv_p[i++]);
	ret = (char *)ft_memalloc(sizeof(char *) * e + i);
	i = 0;
	while (argv_p && argv_p[i])
		ret = ft_strjoin_free(ft_strjoin_free(ret, " ", 0), argv_p[i++], 0);
	return (ret);
}

int		get_id_max_job()
{
	t_list	*tmp;
	t_job	*j;
	int		res;

	tmp = g_job_order;
	res = 1;
	while (tmp)
	{
		j = (t_job*)(tmp->content);
		if (j && j->num >= res)
			res = j->num + 1;
		tmp = tmp->next;
	}
	return (res);
}	

t_job	*ft_create_jobs(t_tree *c)
{
	t_job	*njob;
	t_job	*tmp;
	t_list	*new_order;

	njob = (t_job *)ft_memalloc(sizeof(t_job));
	new_order = ft_lstnew(NULL, 0);
	new_order->content = njob;
	DEBUG("before recup command \n");
	if (c)
		njob->command = get_command(njob->command, c);
	else
		njob->command = get_command_from_process(g_current_execute->argv);
	DEBUG("after recup command \n");
	njob->num = get_id_max_job();
	DEBUG("after recup num \n");
	if (g_job_order)
		new_order->next = g_job_order;
	g_job_order = new_order;
	tmp = g_first_job;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = njob;
	else
		g_first_job = njob;
	
	DEBUG("fin create job\n");
	return (njob);
	// t_job	*njob;
	// t_job	*tmp;
	// t_list	*new_order;

	// njob = (t_job *)ft_memalloc(sizeof(t_job));
	// new_order = ft_lstnew(NULL, 0);
	// if (g_first_job)
	// {
	// 	tmp = g_job_order->content;
	// 	new_order->next = g_job_order;
	// 	njob->command = get_command_from_process(g_current_execute->argv);
	// 	new_order->content = njob;
	// 	njob->num = tmp->num + 1;
	// 	njob->process = g_current_execute;
	// 	g_job_order = new_order;
	// }
	// else
	// {
	// 	new_order->content = njob;
	// 	g_first_job = new_order->content;
	// 	g_first_job->num = 1;
	// 	g_first_job->process = g_current_execute;
	// 	g_job_order = new_order;
	// }
}

void	ft_need_jobs(t_tree *c)
{
	t_job	*njob;
	// t_job	*tmp;
	// t_list	*new_order;

	// njob = (t_job *)ft_memalloc(sizeof(t_job));
	// new_order = ft_lstnew(NULL, 0);
	// new_order->content = njob;
	// DEBUG("before recup command \n");
	// if (c)
	// 	njob->command = get_command(njob->command, c);
	// else
	// 	njob->command = get_command_from_process(g_current_execute->argv);
	// DEBUG("after recup command \n");
	// njob->num = get_id_max_job();
	// DEBUG("after recup num \n");
	// if (g_job_order)
	// 	new_order->next = g_job_order;
	// g_job_order = new_order;
	// tmp = g_first_job;
	// while (tmp && tmp->next)
	// 	tmp = tmp->next;
	// if (tmp)
	// 	tmp->next = njob;
	// else
	// 	g_first_job = njob;
	
	// DEBUG("fin create job\n");
	njob = ft_create_jobs(c);
	// if (first_job)
	// {
	// 	tmp = job_order->content;
	// 	new_order->next = job_order;
	// 	njob->command = get_command(njob->command, c);
	// 	new_order->content = njob;
	// 	njob->num = tmp->num + 1;
	// 	job_order = new_order;
	// }
	// else
	// {
	// 	new_order->content = njob;
	// 	first_job = new_order->content;
	// 	first_job->command = get_command(first_job->command, c);
	// 	first_job->num = 1;
	// 	job_order = new_order;
	// }

	check_run_v2(c, njob);
}
