/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:20:16 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 11:23:04 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_job	*get_job_id(int id)
{
	t_list	*tmp;
	t_job	*j;

	if (g_job_order == NULL || g_job_order->content == NULL)
		return (NULL);
	tmp = g_job_order;
	while (tmp != NULL)
	{
		j = (t_job*)(tmp->content);
		if (j == NULL)
			continue ;
		if (j->num == id)
			return (j);
		tmp = tmp->next;
	}
	return (NULL);
}

t_job	*get_job_minus(void)
{
	if (g_job_order != NULL && g_job_order->next != NULL)
		return ((t_job*)(g_job_order->next->content));
	return (NULL);
}

t_job	*get_job_name(char *name)
{
	t_job	*tmp;

	tmp = g_first_job;
	while (tmp)
	{
		if (ft_strncmp(tmp->command, name, ft_strlen(name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_job	*get_job_plus(void)
{
	if (g_job_order != NULL)
		return ((t_job*)(g_job_order->content));
	return (NULL);
}

t_job	*get_job(char *arg)
{
	int	id;

	if (arg == NULL)
		return (get_job_plus());
	if (!ft_strcmp(arg, "%"))
		return (get_job_plus());
	if (!ft_strncmp(arg, "%%", 2))
		return (get_job_plus());
	if (!ft_strncmp(arg, "%+", 2) || !ft_strncmp(arg, "+", 1))
		return (get_job_plus());
	if (!ft_strcmp(arg, "%-") || !ft_strcmp(arg, "-"))
		return (get_job_minus());
	id = arg[0] == '%' ? ft_atoi(arg + 1) : ft_atoi(arg);
	if (id != 0)
		return (get_job_id(id));
	return (get_job_name(arg[0] == '%' ? arg + 1 : arg));
}
