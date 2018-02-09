/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill_jobs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:30 by maastie           #+#    #+#             */
/*   Updated: 2018/01/11 16:07:31 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	int closefd[3];
extern	int	returned;


void	init_closefd(int pdes[3])
{
	pdes[0] = STDIN_FILENO;
	pdes[1] = STDOUT_FILENO;
	pdes[2] = STDERR_FILENO;
}

void	reset_fd(int pdes[3], t_process *p)
{
	dup2(p->stdin, pdes[0]);
	dup2(p->stdout, pdes[1]);
	dup2(p->stderr, pdes[2]);
}

int			ft_pipe(t_tree *first, t_tree *second)
{
	pid_t	f;

	if (pipe(closefd) == -1 || (f = fork()) == -1)
		return (-1);
	else
	{
		if (f == 0)
		{
			dup2(closefd[1], STDOUT_FILENO);
			close(closefd[0]);
			exit(returned = execute_run(first, second));
		}
		else
		{
			waitpid(f, &returned, WUNTRACED | WCONTINUED | WNOHANG);
			dup2(closefd[0], STDIN_FILENO);
			close(closefd[1]);
			returned = (set_for_pipe(second->right));
			return (returned);
		}
	}
	return (0);
}

int		set_for_pipe(t_tree *c)
{
	t_tree 		*tmp;
	t_tree 		*first_cmd;

	first_cmd = c;
	tmp = c;
	while (tmp)
	{
		if (tmp->token.id == PIPE)
		{
			if (ft_pipe(first_cmd, tmp) == -1)
				return (-1);
			return (0);
		}
		tmp = tmp->right;
	}
	return (returned = execute_run(first_cmd, tmp));
}

char	*get_command(char *ret, t_tree *chead)
{
	t_tree	*tmp;

	tmp = chead;
	while (tmp)
	{
		ret = ft_strjoin_free(ft_strjoin_free(ret, tmp->token.str, 0), " ", 0);
		tmp = tmp->right;
	}
	return (ret);
}