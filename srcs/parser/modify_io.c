/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:31:14 by maastie           #+#    #+#             */
/*   Updated: 2018/03/19 11:55:05 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			greatand(int fd, t_tree *c, t_process *p)
{
	int		ofd;

	ofd = ft_isint(c->token.str) ? ft_atoi(c->token.str) : -1;
	if (ofd == -1 && ft_memcmp(c->token.str, "-", ft_strlen(c->token.str)) == 0)
		ofd = -1;
	else if (ofd == -1 && (ofd = open(c->token.str, O_CREAT |
		O_TRUNC | O_WRONLY, 0755)) == -1)
	{
		sh_error(-1, 0, NULL, 2, c->token.str, " open failed\n");
		return (-1);
	}
	just_the_last(p);
	if (fd == 1 && ofd == -1)
		p->closeout = 1;
	else if (fd == 0 && ofd == -1)
		p->closein = 1;
	else if (fd == 2 && ofd == -1)
		p->closeerr = 1;
	else if (fd == 1)
		p->stdout = ofd;
	else if (fd == 2)
		p->stderr = ofd;
	else if (fd == 0)
		p->stdin = ofd;
	return (0);
}

int			lessand(int fd, t_tree *c, t_process *p)
{
	int		ofd;

	ofd = ft_isint(c->token.str) ? ft_atoi(c->token.str) : -1;
	if (ofd == -1 && ft_memcmp(c->token.str, "-", ft_strlen(c->token.str)) == 0)
		ofd = -1;
	else
	{
		sh_error(-1, 0, NULL, 2, c->token.str, " file number execpted\n");
		return (-1);
	}
	just_the_last(p);
	if (fd == 0 && ofd == -1)
		p->closein = 1;
	else if (fd == 1 && ofd == -1)
		p->closeout = 1;
	else if (fd == 2 && ofd == -1)
		p->closeerr = 1;
	else if (fd == 1)
		p->stdout = ofd;
	else if (fd == 2)
		p->stderr = ofd;
	else if (fd == 0)
		p->stdin = ofd;
	return (0);
}

int			great(int fd, t_tree *c, t_process *p)
{
	int		ofd;

	if ((ofd = open(c->token.str, O_CREAT |
		O_TRUNC | O_WRONLY, 0755)) == -1)
	{
		sh_error(0, 0, NULL, 3, "Error: ",
			c->token.str, " open failed\n");
		return (-1);
	}
	if (fd == 1)
		p->stdout = ofd;
	else if (fd == 2)
		p->stderr = ofd;
	else if (fd == 0)
		p->stdin = ofd;
	else
		p->stdout = ofd;
	return (0);
}

int			modify_fd(int fd, t_tree *c, t_process *p)
{
	if (c->token.id == GREATAND)
		return (greatand(fd, c->right, p));
	else if (c->token.id == LESSAND)
		return (lessand(fd, c->right, p));
	else if (c->token.id == GREAT)
		return (great(fd, c->right, p));
	else if (c->token.id == LESS)
		return (less(fd, c->right, p));
	return (0);
}

t_tree		*modify_io(t_process *p, t_tree *clist)
{
	int	fd;

	fd = ft_isint(clist->token.str) ? ft_atoi(clist->token.str) : -1;
	if (fcntl(fd, F_GETFD) == -1)
	{
		if (ft_memcmp(clist->token.str, "-", 1) == 0)
			fd = -1;
		else if (fd != 0 && fd != 2 && fd != 1 && fd != -1)
			add_in_arguments(p, clist);
		else if (((fd = open(clist->token.str, O_WRONLY, 0755))) == -1)
		{
			sh_error(0, 0, NULL, 2, clist->token.str,
				" is not set as file descriptor\n");
			return ((void *)1);
		}
	}
	if (modify_fd(fd, clist->right, p) == -1)
		return ((void *)1);
	return (clist->right->right->right);
}
