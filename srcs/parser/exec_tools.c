/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:42:59 by maastie           #+#    #+#             */
/*   Updated: 2018/03/28 21:54:44 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			clear_execute(char **path, t_process *p)
{
	(void)p;
	ft_free_array(path);
	return (g_sh.exitstatus);
}

void		sh_remove_fd(t_fd *fd)
{
	ft_strdel(&fd->right_str);
	ft_strdel(&fd->left_str);
	free(fd);
}

void		remove_here(t_process *p)
{
	while (p->fd_list)
	{
		ft_lst_remove_index(&g_here_list, 0, sh_heredoc_remove);
		ft_lst_remove_index(&p->fd_list, 0, sh_remove_fd);
	}
}

void		pere(t_job *j, t_process *pr, int p[2][2], char **env)
{
	t_list		*tmp;

	if (pr->pid && !j->pgid)
	{
		j->pgid = pr->pid;
		setpgid(pr->pid, j->pgid);
		if (j->foreground == 1 && tcsetpgrp(g_shell_terminal, j->pgid) == -1)
			exit(sh_error(1, 0, NULL, 1, "Erreur tcsetpgrp launch_process\n"));
	}
	setpgid(pr->pid, j->pgid);
	if (!pr->pid)
		executor(j, pr, p, env);
	if (!pr->argv && pr->fd_list)
		remove_here(pr);
	tmp = pr->open_fd;
	while (tmp)
	{
		close(*(int*)tmp->content);
		tmp = tmp->next;
	}
	if (pr != j->process)
		close(p[1][0]);
	p[1][0] = p[0][0];
}
