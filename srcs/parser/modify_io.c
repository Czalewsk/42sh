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

extern int closefd[2];

int	greatand(int fd, t_tree *c, t_process *p)
{
	int	ofd;

	(void)p;
	close(fd);
	ofd = -1;
	if (c->token.str[0] >= '0' && c->token.str[0] <= '9')
		ofd = ft_atoi(c->token.str);
	else if (ft_memcmp(c->token.str, "-", ft_strlen(c->token.str)) == 0)
		ofd = -1;
	else if ((ofd = open(c->token.str, O_CREAT | O_TRUNC | O_WRONLY, 0755)) == -1)
		return (-1);
	if (ofd != -1)
		dup2(fd, ofd);
	return (0);
}

int	lessand(int fd, t_tree *c, t_process *p)
{
	int	ofd;

	(void)p;
	ofd = -1;
	if (c->token.str[0] >= '0' && c->token.str[0] <= '9')
		ofd = ft_atoi(c->token.str);
	if (fcntl(ofd, F_GETFD) == -1)
	{
		ft_printf("\nError, %s is not set as file descriptor\n", c->token.str);
		return (-1);
	}
	// if (fd == -1)
	// {}
	// else 
	if (fd != ofd)
		dup2(ofd, fd);
	// if (fd == p->stdin)
	// {
	// 	close(ofd);
	// 	dup2(p->stdin, ofd);
	// }
	// else if (fd == p->stdout)
	// {
	// 	close(p->stdout);
	// 	dup2(p->stdout, ofd);
	// }
	// else if (fd == p->stderr)
	// {
	// 	close(p->stdin);
	// 	dup2(p->stdin, ofd);
	// }
	// else
	// {
	// 	close(fd);
	// 	dup2(fd, ofd);
	// }
	return (0);
}

t_tree	*ft_great(t_process *p, t_tree *c)
{
	(void)p;
	close(STDOUT_FILENO);
	if ((closefd[1] = open(c->right->token.str, O_CREAT | O_TRUNC | O_WRONLY, 0755)) == -1)
		return (NULL);
	dup2(STDOUT_FILENO, closefd[1]);
	c = c->right->right;
	return (c);
}

t_tree	*land(t_process *p, t_tree *c)
{	
	int	fd;

	fd = -1;
	(void)p;
	if (c->right->token.str[0] >= '0' && c->right->token.str[0] <= '9')
	{
		fd = ft_atoi(c->right->token.str);
		if (fcntl(fd, F_GETFD) == -1)
		{
			ft_printf("\nError, %s is not set as file descriptor\n", c->right->token.str);
			return (NULL);
		}
	}
	if (fd != -1 && fd != closefd[0])
		dup2(closefd[0], fd);
	return (c->right->right);
}

// t_tree	*dgand(t_process *p, t_tree *c)
// {
// 	return (c->right->right);
// }
t_tree	*gand(t_process *p, t_tree *c)
{
	(void)p;
	if (c->right->token.str[0] >= '0' && c->right->token.str[0] <= '9')
	{
		closefd[1] = ft_atoi(c->right->token.str);
		if (fcntl(closefd[1], F_GETFD) == -1)
		{
			ft_printf("\nError, %s is not set as file descriptor\n", c->right->token.str);
			return ((void *)1);
		}
	}
	else
	{
		close(STDOUT_FILENO);
		 if ((closefd[1] = open(c->right->token.str, O_CREAT | O_TRUNC | O_WRONLY, 0755)) == -1)
			return ((void*)1);	
		dup2(STDOUT_FILENO, closefd[1]);
	}
	return (c->right->right);
}

t_tree	*ft_dgreat(t_process *p, t_tree *c)
{
	(void)p;
	close(STDOUT_FILENO);
	if ((closefd[1] = (open(c->right->token.str, O_APPEND | O_CREAT | O_WRONLY, 0755))) == -1)
		return (NULL);
	dup2(STDOUT_FILENO, closefd[1]);
	c = c->right->right;
	return (c);
}

t_tree	*ft_less(t_process *p, t_tree *c)
{
	(void)p;
	close(STDIN_FILENO);
	if ((closefd[0] = (open(c->right->token.str, O_RDONLY, 0755))) == -1)
		return (NULL);
	dup2(STDIN_FILENO, closefd[0]);
	c = c->right->right;
	return (c);
}

int	modify_fd(int fd, t_tree *c, t_process *p)
{
	if (c->token.id == GREATAND)
		return (greatand(fd, c->right, p));
	else if (c->token.id == LESSAND)
		return (lessand(fd, c->right, p));
	// if (fd == job->first_process->stdin)
	// {}
	// else if (fd == job->first_process->stdout)
	// {}
	// else if (fd == job->first_process->stderr)
	// {}
	// else
	// {}
	return (0);
}

t_tree	*modify_io(t_process *p, t_tree *clist)
{
	int	fd;

	(void)p;
	fd = ft_atoi(clist->token.str);
	if (fcntl(fd, F_GETFD) == -1)
	{
		if (((fd = open(clist->token.str, O_WRONLY))) == -1)
			ft_printf("\nError, %s is not set as file descriptor\n", clist->token.str);
	}
	else
	{
		if (modify_fd(fd, clist->right, p) == -1)
			return (NULL);
	}
	// // if (ft_strcmp(clist->token.str, "0") == 0)
	// // else if (ft_strcmp(clist->token.str, "1") == 0)
	// // else if (ft_strcmp(clist->token.str, "2") == 0)
	return (clist->right->right->right);
}