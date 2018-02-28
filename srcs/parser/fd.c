/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 19:44:57 by maastie           #+#    #+#             */
/*   Updated: 2018/02/24 19:44:57 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree	*ft_great(t_process *p, t_tree *c)
{
	(void)p;
	close(STDOUT_FILENO);
	if ((g_sh.fds[1] = open(c->right->token.str, O_CREAT |
		O_TRUNC | O_WRONLY, 0755)) == -1)
		return ((void *)1);
	dup2(STDOUT_FILENO, g_sh.fds[1]);
	c = c->right->right;
	return (c);
}

t_tree	*land(t_process *p, t_tree *c)
{
	int	fd;

	(void)p;
	if (ft_str_isdigit(c->right->token.str) == 1)
	{
		fd = ft_atoi(c->right->token.str);
		if (fcntl(fd, F_GETFD) == -1)
		{
			sh_error(0, 0, NULL, 3, "Error, ",
				c->right->token.str, " is not set as file descriptor\n");
			return ((void *)1);
		}
		if (fd != 0)
		{
			close(STDIN_FILENO);
			dup2(STDIN_FILENO, fd);
		}
		return (c->right->right);
	}
	if (ft_memcmp(c->right->token.str, "-",
		ft_strlen(c->right->token.str)) == 0)
	{
		close(STDIN_FILENO);
		return (c->right->right);
	}
	sh_error(-1, 0, NULL, 1, "Error, file number execpted\n");
	return ((void *)1);
}

t_tree	*gand(t_process *p, t_tree *c)
{
	(void)p;
	if (ft_str_isdigit(c->right->token.str) == 1)
	{
		g_sh.fds[1] = ft_atoi(c->right->token.str);
		if (fcntl(g_sh.fds[1], F_GETFD) == -1)
		{
			sh_error(0, 0, NULL, 3, "Error, ",
				c->right->token.str, " is not set as file descriptor\n");
			return ((void *)1);
		}
		dup2(dup2(g_sh.fds[1], STDOUT_FILENO), STDERR_FILENO);
		return (c->right->right);
	}
	else
	{
		close(STDOUT_FILENO);
		if (ft_memcmp("-", c->right->token.str,
			ft_strlen(c->right->token.str)) == 0)
			return (c->right->right);
		else if ((g_sh.fds[1] = open(c->right->token.str, O_CREAT |
			O_TRUNC | O_WRONLY, 0755)) == -1)
			return ((void*)1);
		dup2(dup2(STDOUT_FILENO, g_sh.fds[1]), STDERR_FILENO);
	}
	return (c->right->right);
}

t_tree	*ft_dgreat(t_process *p, t_tree *c)
{
	(void)p;
	close(STDOUT_FILENO);
	if ((g_sh.fds[1] = (open(c->right->token.str, O_APPEND |
		O_CREAT | O_WRONLY, 0755))) == -1)
		return ((void *)1);
	dup2(STDOUT_FILENO, g_sh.fds[1]);
	c = c->right->right;
	return (c);
}

t_tree	*ft_less(t_process *p, t_tree *c)
{
	(void)p;
	close(STDIN_FILENO);
	if ((g_sh.fds[0] = (open(c->right->token.str, O_RDONLY, 0755))) == -1)
		return ((void *)1);
	dup2(STDIN_FILENO, g_sh.fds[0]);
	c = c->right->right;
	return (c);
}
