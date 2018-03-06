/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:49:17 by maastie           #+#    #+#             */
/*   Updated: 2018/03/04 12:37:13 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_job			*first_job;
t_list			*job_order;
t_process		*current_execute;
pid_t			shell_pgid;
struct termios	shell_tmodes;
int				shell_terminal;
int				shell_is_interactive;

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

	tmp = job_order;
	res = 1;
	while (tmp)
	{
		j = (t_job*)(tmp->content);
		DEBUG("jobs.c ligne 51 : cmd du JOB : %s\n", j->command);
		if (j && j->num >= res)
			res = j->num + 1;
		tmp = tmp->next;
	}
	return (res);
}

void	ft_create_jobs(t_tree *c)
{
	t_job	*njob;
	t_job	*tmp;
	t_list	*new_order;

	njob = (t_job *)ft_memalloc(sizeof(t_job));
	new_order = ft_lstnew(NULL, 0);
	new_order->content = njob;
	njob->command = get_command(njob->command, c);
	njob->num = get_id_max_job();
	if (job_order)
		new_order->next = job_order;
	job_order = new_order;
	tmp = first_job;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = njob;
	else
		first_job = njob;
	check_run_v2(c, njob);
}
