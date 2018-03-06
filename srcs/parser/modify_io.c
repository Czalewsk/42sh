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
	// int		ofd;

	// (void)p;
	// close(fd);
	// ofd = -1;
	// if (ft_str_isdigit(c->token.str) == 1)
	// 	ofd = ft_atoi(c->token.str);
	// else if (ft_memcmp(c->token.str, "-", ft_strlen(c->token.str)) == 0)
	// 	ofd = -1;
	// else if ((ofd = open(c->token.str, O_CREAT |
	// 	O_TRUNC | O_WRONLY, 0755)) == -1)
	// 	return (-1);
	// if (ofd != -1)
	// 	dup2(dup2(ofd, fd), STDERR_FILENO);
	// return (0);
	int		ofd;

	(void)p;
	close(fd);
	ofd = -1;
	if (ft_str_isdigit(c->token.str) == 1)
		ofd = ft_atoi(c->token.str);
	else if (ft_memcmp(c->token.str, "-", ft_strlen(c->token.str)) == 0)
		ofd = -1;
	else if ((ofd = open(c->token.str, O_CREAT |
		O_TRUNC | O_WRONLY, 0755)) == -1)
		return (-1);
	if (ofd != -1)
		dup2(dup2(ofd, fd), STDERR_FILENO);
	return (0);
}

int			lessand(int fd, t_tree *c, t_process *p)
{
	int		ofd;

	(void)p;
	ofd = -1;
	if (ft_str_isdigit(c->token.str) == 1)
	{
		p->stdin = ft_atoi(c->token.str);
		if (fcntl(ofd, F_GETFD) == -1)
		{
			sh_error(-1, 0, NULL, 2, c->token.str,
				" is not set as file descriptor\n");
			return (-1);
		}
		if (fd != ofd)
			dup2(dup2(ofd, fd), STDERR_FILENO);
		return (0);
	}
	sh_error(-1, 0, NULL, 1, "Error, file number execpted\n");
	return (-1);
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
			sh_error(0, 0, NULL, 2, clist->token.str,
				" is not set as file descriptor\n");
			return ((void *)1);
		}
	}
	else if (modify_fd(fd, clist->right, p) == -1)
		return ((void *)1);
	return (clist->right->right->right);
}
