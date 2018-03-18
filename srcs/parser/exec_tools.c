/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:42:59 by maastie           #+#    #+#             */
/*   Updated: 2018/03/13 14:42:59 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// void			set_fd(t_process *p)
// {
// 	if (p->stdin != STDIN_FILENO)
// 		dup2(p->stdin, STDIN_FILENO);
// 	if (p->stdout != STDOUT_FILENO)
// 	{
// 		close(STDOUT_FILENO);
// 		dup2(p->stdout, STDOUT_FILENO);
// 	}
// 	if (p->stderr != STDERR_FILENO)
// 	{
// 		close(STDERR_FILENO);
// 		dup2(p->stderr, STDERR_FILENO);
// 	}
// }

void		reset_fdd(t_process *p)
{
	close(p->stdin);
	dup2(g_sh.fds[0], STDIN_FILENO);
	close(p->stdout);
	dup2(g_sh.fds[1], STDOUT_FILENO);
	close(p->stderr);
	dup2(g_sh.fds[2], STDERR_FILENO);
}

int			clear_execute(char **path, t_process *p)
{
	(void)p;
	ft_free_array(path);
	return (g_sh.exitstatus);
}