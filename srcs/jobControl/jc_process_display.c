/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_process_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 09:43:08 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/29 11:40:42 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char *g_tab[] = {
	"Hangup: 1",
	"Interrupt: 2",
	"Quit: 3",
	"Illegal instruction: 4",
	"Trace/BPT trap: 5",
	"Abort trap: 6",
	"EMT trap: 7",
	"Floating point exception: 8",
	"Killed: 9",
	"Bus error: 10",
	"Segmentation fault: 11",
	"Bad system call: 12",
	"Broken pipe: 13",
	"Alarm clock: 14",
	"Terminated: 15",
	"Urgent I/O condition: 16",
	"Suspended (signal): 17",
	"Suspended: 18",
	"Continued: 19",
	"Child exited: 20",
	"Stopped (tty input): 21",
	"Stopped (tty output): 22",
	"I/O possible: 23",
	"Cputime limit exceeded: 24",
	"Filesize limit exceeded: 25",
	"Virtual timer expired: 26",
	"Profiling timer expired: 27",
	"Window size changes: 28",
	"Information request: 29",
	"User defined signal 1: 30",
	"User defined signal 2: 31"
};

static char	*get_printable_state(t_process *p)
{
	char	*state;
	char	*num_signal;

	state = (char*)ft_memalloc(sizeof(char) * 50);
	if (p->state == PROCESS_COMPLETED)
	{
		if (WIFSIGNALED(p->status))
			ft_strcat(state, g_tab[WTERMSIG(p->status) - 1]);
		else if (p->status == 0)
			ft_strcat(state, "Done");
		else
		{
			num_signal = ft_itoa(WEXITSTATUS(p->status));
			ft_strcat(state, "exit: ");
			ft_strcat(state, num_signal);
			ft_memdel((void**)&num_signal);
		}
	}
	else if (p->state == PROCESS_STOPPED)
		ft_strcat(state, "Stopped");
	else
		ft_strcat(state, "Running");
	return (state);
}

static void	add_nb_empty_space(char *str, int nb)
{
	int	i;

	i = -1;
	while (++i < nb)
		if (!str[i])
			str[i] = ' ';
}

void		process_display_long(t_process *p, char *cmd)
{
	t_process	*tmp;
	char		**cmd_process;
	char		*state;
	int			i;

	tmp = p;
	cmd_process = ft_strsplit(cmd, '|');
	i = 0;
	if (cmd_process == NULL)
		exit(sh_error(1, 0, NULL, 1, "fail malloc: process_display_long\n"));
	while (tmp)
	{
		if (i != 0)
			ft_printf("      ");
		state = get_printable_state(tmp);
		add_nb_empty_space(state, 20);
		ft_printf("%d	%s	%s%s\n", tmp->pid,
			state, cmd_process[i], tmp->next == NULL ? " " : "|");
		tmp = tmp->next;
		ft_memdel((void**)&state);
		i++;
	}
	ft_free_array(cmd_process);
}

void		process_display_short(t_process *p, char *cmd, int fd)
{
	char		*state;
	t_process	*tmp;

	tmp = p;
	while (tmp->next)
		tmp = tmp->next;
	state = get_printable_state(tmp);
	add_nb_empty_space(state, 20);
	ft_putstr_fd(state, fd);
	ft_putendl_fd(cmd, fd);
	ft_memdel((void**)&state);
}
