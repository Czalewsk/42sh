/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:42:59 by maastie           #+#    #+#             */
/*   Updated: 2018/03/19 13:33:07 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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
