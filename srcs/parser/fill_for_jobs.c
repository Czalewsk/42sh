/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/01/02 17:31:28 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	t_fill_job	g_fill_jobs[];

// void	ft_affiche_procces(t_process *p)// tmp
// {
// 	t_process *tp;
// 	int	i;

// 	ft_printf("\nNew_process\n");
// 	tp = p;
// 	while (tp)
// 	{
// 		i = 0;
// 		while (tp->argv && tp->argv[i])
// 			ft_printf("\n%s\n", tp->argv[i++]);
// 		tp = tp->next;
// 		if (tp)
// 			ft_printf("\n PIPED TO\n");
// 	}
// }

// void	ft_affiche_job(t_job *job)
// {
// 	t_job	*tjob;

// 	tjob = job;
// 	ft_printf("New_job\n");
// 	while (tjob)
// 	{
// 		ft_affiche_procces(tjob->first_process);
// 		if (tjob->next)
// 			ft_printf(" \"1 &&\" \"2 ||\" 0 rien --->%d\nNew Job\n", tjob->next->andor);
// 		tjob = tjob->next;
// 	}
// }

// void	ft_affiche_run(t_run *run)// tmp
// {
// 	t_run *trun;

// 	ft_printf("\nFirst run\n");
// 	trun = run;
// 	while (trun)
// 	{
// 		ft_affiche_job(trun->job);
// 		trun = trun->next;
// 		if (trun)
// 			ft_printf("New Run\n");
// 	}
// }

t_run	*fill_run(t_run *run, t_tree *clist)
{
	t_job		*fj;
	t_process	*fp;
	t_tree		*tmp;
	int			i;

	i = 0;
	tmp = clist;
	// ft_printf("\nTEST\n");
	// while (clist)
	// {
	// 	ft_printf("\n%s\n", clist->token.str);
	// 	clist = clist->right;
	// }
	// ft_printf("\nEND TEST\n");
	// return (run);
	run->command = get_command(run->command, tmp);
	run->job = (t_job *)ft_memalloc(sizeof(t_job));
	run->job->first_process = init_process(run->job->first_process);
	fp = run->job->first_process;
	fj = run->job;
	while (tmp && g_fill_jobs[i].fjob)
	{
		if (tmp && g_fill_jobs[i].one == tmp->token.id)
		{
			tmp = g_fill_jobs[i].fjob(run, tmp);
			i = -1;
		}
		i++;
	}
	run->job = fj;
	run->job->first_process = fp;
	return (run);
}

int		exec_acces(char *tmp, int ret, char **argv)
{
	pid_t	father;

	if (access(tmp, X_OK) != -1)
	{
		if ((father = fork()) == -1)
			exit(-1);
		if (father == 0)
			exit(ret = execve(tmp, argv, g_sh.env));
		else
		{
			waitpid(father, &ret, WUNTRACED | WCONTINUED);
			return (ret);
		}
	}
	return (-1);
}

int		execute_run(t_run *run)
{
	char	**path;
	char	*exec_line;
	int		i;
	int		ret;

	i = 0;
	path = ft_strsplit("/Users/maastie/.brew/bin:/Users/maastie/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/Applications/VMware", ':');
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i], "/");
		exec_line = ft_strjoin_free(exec_line, run->job->first_process->argv[0], 0);
		ret = exec_acces(exec_line, ret, run->job->first_process->argv);
		if (ret == 0)
		{
			// termcaps_set_tty();
			// dup2(STDOUT_FILENO, 1);
			// dup2(STDERR_FILENO, 2);
			// dup2(STDIN_FILENO, 0);
			ft_strdel(&exec_line);
			ft_free_array(path);
			return (ret);
		}
		ft_strdel(&exec_line);
		i++;
	}

	ft_free_array(path);
//	ft_printf("\nerreur command not found %s\n", run->job->first_process->argv[0]);
	return (-1);
}

int		ft_fill_for_jobs(t_tree *head)
{
	t_run	*first_run;
	t_run	*n;
	t_tree	*tmp;
	int		ret_exec;

	tmp = head;
	ret_exec = 0;
	n = (t_run *)ft_memalloc(sizeof(t_run));
	first_run = n;
	while (tmp)
	{
		n = fill_run(n, tmp);
		tmp = tmp->left;
		ft_printf("\n");
		ret_exec = execute_run(n);
		if (ret_exec != 0)
		{
			if (ret_exec == -1)
			{
				if (n->job->andor == 2)
					break ;
				else if (n->job->andor == 1)
				{
					ft_free_runs(first_run);
					return (ft_free_tree(head));
					return (-1);
				}
			}
		}
		dup2(1, STDOUT_FILENO);
		dup2(2, STDERR_FILENO);
		dup2(0, STDIN_FILENO);
		if (tmp)
		{
			n->next = (t_run *)ft_memalloc(sizeof(t_run));
			n = n->next;
		}
	}
	n = first_run;
//	ft_affiche_run(n);
	ft_free_runs(first_run);
	return (ft_free_tree(head));
}
