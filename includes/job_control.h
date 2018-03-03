/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 12:53:03 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 11:12:20 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include <sys/types.h>
# include <termios.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>



typedef struct 			s_process
{
	char				**argv;
	pid_t				pid;        /* process ID */
	char				completed;  /* true if process has completed */
	char				stopped;    /* true if process has stopped */
	int					status;     /* reported status value */
	int					stdin;
	int					stdout;
	int					stderr;
}						t_process;

typedef struct 			s_job
{
	struct s_job		*next;
	t_process			*process;
	int					num;
	char				*command;		/* command line, used for messages */
	char				notified;		/* true if user told about stopped job */
	pid_t				pgid;			/* process group ID */
	struct termios		tmodes;			/* saved terminal modes */
}						t_job;

t_job			*first_job;
t_list			*job_order;
t_process		*current_execute;
t_job			*first_job;
pid_t			shell_pgid;
struct termios	shell_tmodes;
int				shell_terminal;
int				shell_is_interactive;




void    put_first_in_job_order(t_job *j) /* Permet de trouver le conteneur list du job en parametre pour le mettre en job actif*/
int		bt_fg(char **arg);
int		bt_bg(char **arg);
t_job   *get_job(char *arg);
t_job   *get_job_plus();
t_job   *get_job_minus();
t_job   *get_job_id(int id);
void	continue_job (t_job *j, int foreground);
void	mark_job_as_running (t_job *j);
void	put_job_in_foreground (t_job *j, int cont);
void  	put_job_in_background (t_job *j, int cont);

/* jobs */
int		jobs_display(t_job *j);
void    process_display_short(t_process *process);
void    process_display_long(t_process *process);
int 	jobs_display_only_id(t_job *j);
int     bt_jobs(char **arg);








t_job	*find_job(pid_t pgid);
int		job_is_stopped(t_job *j);
int		job_is_completed(t_job *j);
void	continue_job (t_job *j, int foreground);
void	do_job_notification (void);
void	format_job_info (t_job *j, const char *status);
void	init_shell ();
void	launch_job (t_job *j, int foreground);
void	launch_process (t_process *p, pid_t pgid, int foreground, char ** env);
void	mark_job_as_running (t_job *j);
int		mark_process_status (pid_t pid, int status);
void	put_job_in_background (t_job *j, int cont);
void	put_job_in_foreground (t_job *j, int cont);
void	update_status (void);
void	wait_for_job (t_job *j);

#endif
