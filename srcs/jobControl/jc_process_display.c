/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_process_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 09:43:08 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 16:03:57 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	get_printable_state(t_process *p)
{
	if (p->state == PROCESS_COMPLETED)
	{
		if (WIFSIGNALED(p->status))
			ft_printf("%s", strsignal(WTERMSIG(p->status)));
		else if (p->status == 0)
			ft_printf("Done");
		else
			ft_printf("exit: %d", WEXITSTATUS(p->status));
	}
	else if (p->state == PROCESS_STOPPED)
		ft_printf("Stopped");
	else
		ft_printf("Running");
}

void		process_display_long(t_process *p, char *cmd)
{
	t_process	*tmp;
	char		**cmd_process;
	int			i;

	tmp = p;
	cmd_process = ft_strsplit(cmd, '|');
	i = 0;
	if (cmd_process == NULL)
		exit(sh_error(1, 0, NULL, 1, "fail malloc: process_display_long\n"));
	while (tmp)
	{
		ft_printf("%d ", tmp->pid);
		get_printable_state(tmp);
		ft_printf("			%c %s\n", i == 0 ? ' ' : '|', cmd_process[i]);
		tmp = tmp->next;
		i++;
	}
	ft_free_array(cmd_process);
}

void		process_display_short(t_process *p, char *cmd)
{
	get_printable_state(p);
	ft_printf("     %s\n", cmd);
}
