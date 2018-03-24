/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:18:10 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/24 10:52:58 by scorbion         ###   ########.fr       */
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

static int		bg_is_launchable(t_job *j, char *arg)
{
	if (j == NULL)
	{
		if (arg == NULL)
			return (sh_error(1, 0, NULL, 1, "bg: current: no such job\n"));
		else
			return (sh_error(1, 0, NULL, 3, "bg: ", arg, ": no such job\n"));
	}
	else if (job_is_completed(j))
		return (sh_error(1, 0, NULL, 1, "bg: job has terminated\n"));
	bg_launch(j);
	return (0);
}

int				bt_bg(t_process *p, int size, char **arg, char **env)
{
	int		i;
	int		retour;

	(void)env;
	(void)p;
	(void)size;
	can_execute_builtin_job_control("bg");
	retour = 0;
	i = 1;
	if (arg[i] == NULL)
		retour = bg_is_launchable(get_job(NULL), NULL);
	while (arg[i])
	{
		retour = bg_is_launchable(get_job(arg[i]), arg[i]) || retour;
		i++;
	}
	return (retour);
}
