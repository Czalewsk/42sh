/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:43:49 by maastie           #+#    #+#             */
/*   Updated: 2018/03/05 19:26:59 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_pipe(t_tree *first, t_tree *second, t_job *job)
{
	pid_t		f;
	int			fd[2];

	if (pipe(fd) == -1 || (f = fork()) == -1)
		return (-1);
	else
	{
		if (f == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			exit(g_sh.exitstatus = set_for_pipe(second->right, job));
			// dup2(fd[1], STDOUT_FILENO);
			// close(fd[0]);
			// exit(g_sh.exitstatus = execute_run(first, second, job));
		}
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			g_sh.exitstatus = execute_run(first, second, job);
			return (g_sh.exitstatus);
			// close(fd[1]);
			// dup2(fd[0], STDIN_FILENO);
			// return (g_sh.exitstatus = set_for_pipe(second->right, job));
		}
	}
	return (g_sh.exitstatus);
}

int				set_for_pipe(t_tree *c, t_job *job)
{
	t_tree		*tmp;
	t_tree		*first_cmd;

	first_cmd = c;
	tmp = c;
	while (tmp)
	{
		if (tmp->token.id == PIPE)
		{
			if (ft_pipe(first_cmd, tmp, job) == -1)
				return (-1);
			return (0);
		}
		tmp = tmp->right;
	}
	return (g_sh.exitstatus = execute_run(first_cmd, tmp, job));
}
