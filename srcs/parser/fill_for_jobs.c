/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/03/28 22:19:57 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	struct termios	s_termios_backup;
extern	t_cmd_action	g_cmd_actions[];

t_tree			*fill_process(t_tree *c, t_process *p)
{
	int			i;

	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	while (c && (c->token.id != AND_IF && c->token.id != OR_IF
		&& c->token.id != PIPE) && c->token.id != SEMI && c->token.id != AND)
	{
		i = -1;
		while (c && g_cmd_actions[++i].fjob)
		{
			if (g_cmd_actions[i].one == c->token.id)
			{
				c = g_cmd_actions[i].fjob(p, c);
				if (c == (void *)1)
					return ((void *)1);
				i = -1;
			}
		}
	}
	return (c);
}

t_tree			*finish_norme(t_job *j, t_tree *c)
{
	if (c && c->token.id != PIPE)
	{
		if (c->token.id != SEMI && c->token.id != AND)
			j->finish_command = cpy_from_tree(c);
	}
	else
		j->finish_command = NULL;
	return (j->finish_command);
}

int				fill_job(t_tree *cc, t_job *j)
{
	t_process	*new;
	t_process	**tmp;
	t_tree		*c;

	c = cc;
	tmp = &j->process;
	while (c && (c->token.id != AND_IF && c->token.id != OR_IF)
		&& c->token.id != SEMI && c->token.id != AND)
	{
		if (c->token.id == PIPE)
			c = c->right;
		new = ft_memalloc(sizeof(t_process));
		*tmp = new;
		tmp = &new->next;
		if ((c = fill_process(c, new)) == (void*)1)
			return (-1);
		j->finish_command = finish_norme(j, c);
	}
	return (0);
}

t_job			*create_new_job(t_tree *c)
{
	t_job		*job;
	t_tree		*tmp;

	if (c == NULL || c == (void *)1)
		return (NULL);
	tmp = c;
	job = (t_job *)ft_memalloc(sizeof(t_job));
	job->command = get_command(job->command, c);
	job->num = get_id_max_job();
	job->tmodes = s_termios_backup;
	job->foreground = 1;
	while (tmp->right && tmp->token.id != AND_IF && tmp->token.id != OR_IF)
		tmp = tmp->right;
	if (tmp->token.id == AND && g_sh.subshellactive == 1)
		tmp->token.id = SEMI;
	else if (tmp->token.id == AND)
		job->foreground = 0;
	if (fill_job(c, job) == -1)
	{
		free_job(job);
		job = NULL;
	}
	return (job);
}

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;
	t_job		*tmp2;

	tmp = head;
	while (tmp && !g_sh_exit)
	{
		tmp2 = create_new_job(tmp);
		while (tmp2 && !g_sh_exit)
		{
			execute_job(tmp2);
			if (!g_shell_is_interactive)
				wait_for_job(tmp2);
			else if (tmp2->is_builtin == 0 && tmp2->foreground)
				tmp2 = put_job_in_foreground(tmp2, 0);
			else if (tmp2->is_builtin == 0)
			{
				put_job_in_background(tmp2, 0);
				tmp2 = NULL;
			}
			else if (tmp2->is_builtin == 1)
				tmp2 = need_norme(tmp2);
		}
		tmp = tmp->left;
	}
	return (ft_free_tree(head));
}
