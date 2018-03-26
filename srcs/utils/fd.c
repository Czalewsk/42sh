/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 20:32:48 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/26 21:29:01 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		init_fd(void)
{
	int		open1;
	int		open2;

	close(11);
	close(12);
	close(13);
	close(14);
	close(15);
	open1 = open(ttyname(0), O_RDONLY);
	open2 = open(ttyname(0), O_WRONLY);
	g_sh.test_fd = dup2(open1, 11);
	g_sh.fd_tty = dup2(open2, 12);
	close(open1);
	close(open2);
	g_sh.fds[0] = dup2(0, 13);
	g_sh.fds[1] = dup2(1, 14);
	g_sh.fds[2] = dup2(2, 15);
}

void		reset_fd(t_list *open_fd)
{
	while (open_fd)
	{
		close(*(int*)open_fd->content);
		open_fd = open_fd->next;
	}
	dup2(g_sh.fds[0], STDIN_FILENO);
	dup2(g_sh.fds[1], STDOUT_FILENO);
	dup2(g_sh.fds[2], STDERR_FILENO);
}
