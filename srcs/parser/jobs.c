/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:49:17 by maastie           #+#    #+#             */
/*   Updated: 2018/03/19 16:03:50 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern struct termios s_termios_backup;

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

int		get_id_max_job(void)
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
	if (c)
		njob->command = get_command(njob->command, c);
	njob->num = get_id_max_job();
	if (g_job_order)
		new_order->next = g_job_order;
	g_job_order = new_order;
	tmp = g_first_job;
	njob->tmodes = s_termios_backup;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = njob;
	else
		g_first_job = njob;
	return (njob);
}
