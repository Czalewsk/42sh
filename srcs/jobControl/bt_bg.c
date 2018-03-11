/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:18:10 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 19:08:05 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void		bg_launch(t_job *j)
{
	char	*num;

	num = ft_itoa(j->num);
	if (job_is_running(j))
		sh_error(0, 0, NULL, 3, "bg: job ", num, " already in background\n");
	else
	{
		ft_printf("[%s]", num);
		if (g_job_order)
		{
			if ((t_job*)(g_job_order->content) == j)
				ft_printf("+");
			else if (g_job_order->next &&
				(t_job*)(g_job_order->next->content) == j)
				ft_printf("-");
			else
				ft_printf(" ");
		}
		ft_printf(" %s &\n", j->command);
		put_first_in_job_order(j);
		continue_job(j, 0);
	}
	free(num);
}

int				bt_bg(t_process *p, int size, char **arg, char **env)
{
	t_job	*tmp;
	int		i;
	int		retour;

	(void)env;
	(void)p;
	(void)size;
	i = 1;
	retour = 0;
	if (arg[i] == NULL)
	{
		tmp = get_job(NULL);
		if (tmp == NULL)
			retour = sh_error(1, 0, NULL, 1, "bg: current: no such job\n");
		else
			bg_launch(tmp);
	}
	while (arg[i])
	{
		tmp = get_job(arg[i]);
		if (tmp == NULL)
			retour = sh_error(1, 0, NULL, 3, "bg: ", *arg, ": no such job\n");
		else
			bg_launch(tmp);
		i++;
	}
	return (retour);
}
