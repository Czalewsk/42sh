/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:37:27 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/29 12:02:41 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			jobs_usage(char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	sh_error(0, 0, NULL, 3, "jobs: -", tmp, ": invalid option\n");
	return (sh_error(1, 0, NULL, 1, "jobs: usage: jobs [-lprs] [jobspec]\n"));
}

static int	jobs_display_jobspec(char info, char run_or_stop, char **arg)
{
	int		i;
	int		retour;
	t_job	*tmp;

	i = 0;
	retour = 0;
	while (arg[i] != NULL)
	{
		tmp = get_job(arg[i]);
		if (tmp == NULL)
			retour = sh_error(1, 0, NULL, 3,
				"jobs: ", arg[i], ": no such job\n");
		else if (run_or_stop == 'r' && job_is_running(tmp) == 0)
			;
		else if (run_or_stop == 's' && job_is_running(tmp) != 0)
			;
		else if (info == 'p')
			jobs_display_only_id(tmp);
		else if (info == 'l')
			jobs_display(tmp, 1, 1);
		else
			jobs_display(tmp, 0, 1);
		i++;
	}
	return (retour);
}

static int	jobs_display_no_jobspec(char info, char run_or_stop)
{
	t_job	*j;
	t_job	*next;

	j = g_first_job;
	while (j != NULL)
	{
		next = j->next;
		if (run_or_stop == 'r' && job_is_running(j) == 0)
			;
		else if (run_or_stop == 's' && job_is_running(j) != 0)
			;
		else if (info == 'p')
			jobs_display_only_id(j);
		else if (info == 'l')
			jobs_display(j, 1, 1);
		else
			jobs_display(j, 0, 1);
		j = next;
	}
	return (0);
}

int			bt_jobs(t_process *p, int size, char **arg, char **env)
{
	char	info;
	char	run_or_stop;
	int		i;
	int		j;

	(void)env;
	(void)p;
	(void)size;
	i = 0;
	info = 0;
	run_or_stop = 0;
	while (arg[++i] && (j = 0) == 0 && arg[i][0] == '-')
		while (arg[i][++j])
			if (arg[i][j] == 'l' || arg[i][j] == 'p')
				info = arg[i][j];
			else if (arg[i][j] == 'r' || arg[i][j] == 's')
				run_or_stop = arg[i][j];
			else
				return (jobs_usage(arg[i][j]));
	if (arg == NULL || arg[i] == NULL)
		jobs_display_no_jobspec(info, run_or_stop);
	else
		jobs_display_jobspec(info, run_or_stop, arg + i);
	return (0);
}
