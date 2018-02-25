/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:31:14 by maastie           #+#    #+#             */
/*   Updated: 2018/01/11 16:31:14 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			greatand(int fd, t_tree *c, t_process *p)
{
	int		ofd;

	(void)p;
	close(fd);
	ofd = -1;
	if (ft_str_isdigit(c->token.str) == 1)
		ofd = ft_atoi(c->token.str);
	else if (ft_memcmp(c->token.str, "-", ft_strlen(c->token.str)) == 0)
		ofd = -1;
	else if ((ofd = open(c->token.str, O_CREAT | O_TRUNC | O_WRONLY, 0755)) == -1)
		return (-1);
	if (ofd != -1)
		dup2(fd, ofd);
	return (0);
}

int			lessand(int fd, t_tree *c, t_process *p)
{
	int		ofd;

	(void)p;
	ofd = -1;
	if (ft_str_isdigit(c->token.str) == 1)
		ofd = ft_atoi(c->token.str);
	if (fcntl(ofd, F_GETFD) == -1)
	{
		ft_printf("Error, %s is not set as file descriptor\n", c->token.str);//
		return (-1);
	}
	if (fd != ofd)
		dup2(ofd, fd);
	return (0);
}

t_tree		*lessgreat(t_process *p, t_tree *c)
{
	(void)p;
	close(STDIN_FILENO);
	if ((g_sh.fds[0] = (open(c->right->token.str, O_RDONLY, 0755))) == -1)
		return ((void *)1);
	dup2(STDIN_FILENO, g_sh.fds[0]);
	if (c->previous == NULL)
	{
		close(STDOUT_FILENO);
		if ((g_sh.fds[1] = (open(c->right->token.str, O_CREAT | O_WRONLY, 0755))) == -1)
			return ((void *)1);
		dup2(STDOUT_FILENO, g_sh.fds[1]);
	}
	return (c->right->right);	
}

int			modify_fd(int fd, t_tree *c, t_process *p)
{
	if (c->token.id == GREATAND)
		return (greatand(fd, c->right, p));
	else if (c->token.id == LESSAND)
		return (lessand(fd, c->right, p));
	return (0);
}

t_tree		*modify_io(t_process *p, t_tree *clist)
{
	int	fd;

	fd = -1;
	if (ft_str_isdigit(clist->token.str) == 1)
		fd = ft_atoi(clist->token.str);
	if (fcntl(fd, F_GETFD) == -1)
	{
		if (((fd = open(clist->token.str, O_WRONLY, 0755))) == -1)
		{
			ft_printf("Error, %s is not set as file descriptor\n", clist->token.str);//
			return ((void *)1);
		}
	}
	else if (modify_fd(fd, clist->right, p) == -1)
		return ((void *)1);
	return (clist->right->right->right);
}