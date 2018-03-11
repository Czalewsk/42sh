/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 12:53:03 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 16:05:43 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "libft.h"
# include <sys/types.h>
# include <termios.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

# define PROCESS_RUNNING 0
# define PROCESS_STOPPED 1
# define PROCESS_COMPLETED 2

typedef struct	s_process
{
	struct s_process	*next;
	char				**argv;
	pid_t				pid;
	int					state;
	int					status;
	int					stdin;
	int					stdout;
	int					stderr;
}				t_process;

typedef struct	s_job
{
	struct s_job		*next;
	struct t_tree		*finish_or_nd_if;
	int					returnedlast;
	int					foni;
	t_process			*process;
	int					num;
	char				*command;
	char				notified;
	pid_t				pgid;
	struct termios		tmodes;
}				t_job;

extern t_job		*g_first_job;
extern t_list		*g_job_order;
extern t_process	*g_current_execute;
extern pid_t		g_shell_pgid;
extern int			g_shell_terminal;
extern int			g_shell_is_interactive;

void			put_first_in_job_order(t_job *j);
int				bt_fg(char **arg);
int				bt_bg(char **arg);
t_job			*get_job(char *arg);
t_job			*get_job_plus();
t_job			*get_job_minus();
t_job			*get_job_id(int id);
void			continue_job (t_job *j, int foreground);
void			mark_job_as_running (t_job *j);
void			put_job_in_foreground(t_job *j, int cont);
void			put_job_in_background(t_job *j, int cont);
void			put_process_in_foreground(t_process *p, int cont);

int				jobs_display(t_job *j, int long_flag);
void			process_display_short(t_process *process, char *cmd);
void			process_display_long(t_process *process, char *cmd);
int				jobs_display_only_id(t_job *j);
void			del_job_in_first(t_job *j);
void			free_job(t_job *j);
int				bt_jobs(char **arg);

void			do_job_notification (void);
void			update_status (void);

int				mark_process_status (pid_t pid, int status);
void			update_status (void);

int				job_is_completed(t_job *j);
int				job_is_stopped(t_job *j);
int				job_is_running(t_job *j);
void			wait_for_job (t_job *j);
char			**cpy_argv_process(char **argv);
t_process		*cpy_profonde_process(t_process *src);
t_list			*pop_job_from_job_order(t_job *j);
void			del_job(t_job *j);
void			clear_completed_job();

void			init_job_control(void);

void			launch_process(char *tmp, t_process *p, t_job *j, char **env);

#endif
