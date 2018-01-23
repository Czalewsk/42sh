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

int	greatand(int fd, t_tree *c, t_process *p)
{
	int	ofd;

	if (c->token.str[0] >= '0' && c->token.str[0] <= '9')
		ofd = ft_atoi(c->token.str);
	else if (((fd = open(c->token.str, O_WRONLY | O_CLOEXEC | O_CREAT))) == -1)
		return (-1);
	if (fd == p->stdin)
	{
		close(p->stdin);
		dup2(p->stdin, ofd);
	}
	else if (fd == p->stdout)
	{
		close(p->stdout);
		dup2(p->stdout, ofd);
	}
	else if (fd == p->stderr)
	{
		close(p->stdin);
		dup2(p->stdin, ofd);
	}
	else
	{
		close(fd);
		dup2(fd, ofd);
	}
	return (0);
}

int	lessand(int fd, t_tree *c, t_process *p)
{
	int	ofd;

	if (c->token.str[0] >= '0' && c->token.str[0] <= '9')
		ofd = ft_atoi(c->token.str);
	else if (((fd = open(c->token.str, O_WRONLY | O_CLOEXEC | O_CREAT))) == -1)
		return (-1);
	if (fd == p->stdin)
	{
		close(ofd);
		dup2(p->stdin, ofd);
	}
	else if (fd == p->stdout)
	{
		close(p->stdout);
		dup2(p->stdout, ofd);
	}
	else if (fd == p->stderr)
	{
		close(p->stdin);
		dup2(p->stdin, ofd);
	}
	else
	{
		close(fd);
		dup2(fd, ofd);
	}
	return (0);
}

t_tree	*ft_great(t_run *run, t_tree *c)
{
	int	fd;

	(void)run;
//	close(STDOUT_FILENO);
	close(run->job->first_process->stdout);
//	close(STDOUT_FILENO);
	ft_printf("\n%d.     .%d\n", run->job->first_process->stdout, STDOUT_FILENO);

	if (((fd = open(c->right->token.str, O_CREAT | O_TRUNC | O_WRONLY | O_CLOEXEC, 0755))) == -1)
		return (NULL);
	// dup(fd)
	dup2(STDOUT_FILENO, fd);
//	dup2(run->job->first_process->stdout, fd);



//	dup2(run->job->first_process->stdout, fd);
	return (c->right->right);
}

t_tree	*ft_dgreat(t_run *run, t_tree *c)
{
	int	fd;

//	(void)run;
	close(run->job->first_process->stdout);
//	close(STDIN_FILENO);
	if ((fd = (open(c->right->token.str, O_CLOEXEC | O_WRONLY | O_APPEND | O_TRUNC, 0755))) == -1)
		return (NULL);
//	dup2(fd, STDIN_FILENO);
//	dup2(run->job->first_process->stdout);
	return (c->right->right);
}

t_tree	*ft_less(t_run *run, t_tree *c)
{
	int	fd;

	close(run->job->first_process->stdin);
	if ((fd = (open(c->right->token.str, O_CLOEXEC | O_WRONLY | O_CREAT))) == -1)
		return (NULL);
	dup2(run->job->first_process->stdout, fd);
	return (c->right->right);
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

t_tree	*modify_io(t_run *run, t_tree *clist)
{
	int	fd;

	fd = ft_atoi(clist->token.str);
	if (fcntl(fd, F_GETFD) == -1)
	{
		if (((fd = open(clist->token.str, O_WRONLY))) == -1)
			ft_printf("\nError, %s is not set as file descriptor\n", clist->token.str);
	}
	else
	{
		if (modify_fd(fd, clist->right, run->job->first_process) == -1)
			return (NULL);
	}
	// // if (ft_strcmp(clist->token.str, "0") == 0)
	// // else if (ft_strcmp(clist->token.str, "1") == 0)
	// // else if (ft_strcmp(clist->token.str, "2") == 0)
	return (clist->right->right->right);
}