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

int	returned;
int closefd[3];

t_process 		*fill_for_exec(t_tree *c, t_tree *stop)
{
	int	i;
	t_process 	*p;

	i = 0;
	p = NULL;
	p = init_process(p);
	if (!stop)
		c  = g_fill_jobs[0].fjob(p, c);
	while (c && g_fill_jobs[i].fjob && c != stop)
	{
		if (c && g_fill_jobs[i].one == c->token.id)
		{
			c = g_fill_jobs[i].fjob(p, c);
			if (c == (void *)1)
			{
				ft_free_process(p);
				return (NULL);
			}
			i = -1;
		}
		i++;
	}
	return (p);
}

int		exec_acces(char *tmp, char **argv)
{
	pid_t	father;

	if ((father = fork()) == -1)
		exit(-1);
	if (father == 0)
		exit(returned = execve(tmp, argv, g_sh.env));
	else
	{
		waitpid(father, &returned, WUNTRACED | WCONTINUED);
	}
	return (returned);
}

int		execute_run(t_tree *c, t_tree *stop)
{
	char		**path;
	char		*exec_line;
	int			i;
	t_process 	*p;

	i = 0;
	p = NULL;
	p = fill_for_exec(c, stop);
	if (p == NULL)
		return (-1);
	path = ft_strsplit("/Users/maastie/.brew/bin:/Users/maastie/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/Applications/VMware", ':');
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i], "/");
		exec_line = ft_strjoin_free(exec_line, p->argv[0], 0);
		if (access(exec_line, X_OK) != -1)
		{
			ft_printf("\n");
			returned = exec_acces(exec_line, p->argv);
			ft_strdel(&exec_line);
			break ;
		}
		ft_strdel(&exec_line);
		i++;
	}
	ft_free_array(path);
	reset_fd(closefd, p);
	ft_free_process(p);
	return (returned);
}

t_tree *get_new_process_from_valid_or_if(t_tree *c)
{
	while (c)
	{
		c = c->right;
		if (c && c->token.id == AND_IF)
			return (c->right);
	}
	return (c);
}

t_tree *get_new_process_from_pipe(t_tree *c)
{
	while (c)
	{
		c = c->right;
		if (c && c->token.id == AND_IF)
		{
			if (returned == -1)
				return (NULL);
			return (c->right);
		}
		else if (c && c->token.id == OR_IF)
		{
			if (returned == 0)
				return(c = get_new_process_from_valid_or_if(c));
			return (c->right);
		}
	}
	return (c);
}

t_tree	*check_run_v2(t_tree *c)
{
	t_tree	*stop;
	t_tree	*tmp;

	tmp = c;
	stop = c;
	while (stop)
	{
		if (stop->token.id == AND_IF)
		{
			if ((returned = execute_run(tmp, stop)) != 0)
				return (NULL);
			tmp = stop->right;
			stop = tmp;
		}
		else if (stop->token.id == OR_IF)
		{
			if ((returned = execute_run(tmp, stop)) == 0)
				tmp = get_new_process_from_valid_or_if(stop->right);
			else
				tmp = stop->right;
			stop = tmp;
		}
		else if (stop->token.id == PIPE)
		{
			if (set_for_pipe(tmp) == 0)
			{
				tmp = get_new_process_from_pipe(stop);
				stop = tmp;
			}
			else
				return (NULL);
		}
		if (stop && stop->right == NULL)
			returned = execute_run(tmp, stop->right);
		if (stop)
			stop = stop->right;
		returned = -1;
	}
	return (c->left);	
}

t_tree	*check_run(t_tree *c)
{
	t_tree *tmp;

	tmp = c;
	while (tmp->right)
		tmp = tmp->right;
	if (tmp->token.id == AND)
		return (c->left);
	return (check_run_v2(c));
}

int		ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;

	tmp = head;
	init_closefd(closefd);
	while (tmp)
		tmp = check_run(tmp);
	return (ft_free_tree(head));
}
