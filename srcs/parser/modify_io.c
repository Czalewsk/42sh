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

extern int closefd[3];

int	fully_digit(char *s) // Utiliser ft_str_isdigi
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	greatand(int fd, t_tree *c, t_process *p)
{
	int	ofd;

	(void)p;
	close(fd);
	ofd = -1;
	if (fully_digit(c->token.str) == 0)
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
	if (fully_digit(c->token.str) == 0)
		ofd = ft_atoi(c->token.str);
	if (fcntl(ofd, F_GETFD) == -1)
	{
		ft_printf("\nError, %s is not set as file descriptor\n", c->token.str);
		return (-1);
	}
	if (fd != ofd)
		dup2(ofd, fd);
	return (0);
}

int		read_hr(char *hr, char *ref)
{
	if (ft_strlen(hr) -1 == 0)
		return (-1);
	else if (ft_memcmp(hr, ref, ft_strlen(hr) -1) != 0)
		return (-1);
	return (0);
}

t_tree	*here_doc(t_process *p, t_tree *c)
{
	char	*hr;
	int		asd[2];

	(void)p;
	if (pipe(asd) == -1)
 		return ((void *)1);// return (sh_error)
 	hr = NULL;
	prompt_add("> ", &hr);
 	while (read_hr(hr, c->right->token.str) != 0)
 	{
 		ft_putstr_fd(hr, asd[1]);
		ft_strdel(&hr);
	 	prompt_add("> ", &hr);
 	}
 	ft_strdel(&hr);
 	close(asd[1]);
 	dup2(asd[0], STDIN_FILENO);
 	close(asd[0]);
 	return (c->right->right);
}

t_tree	*ft_great(t_process *p, t_tree *c)
{
	(void)p;
	close(STDOUT_FILENO);
	if ((closefd[1] = open(c->right->token.str, O_CREAT | O_TRUNC | O_WRONLY, 0755)) == -1)
		return ((void *)1);
	dup2(STDOUT_FILENO, closefd[1]);
	c = c->right->right;
	return (c);
}

t_tree	*land(t_process *p, t_tree *c)
{	
	int	fd;

	fd = -1;
	(void)p;
	if (fully_digit(c->right->token.str) == 0)
	{
		fd = ft_atoi(c->right->token.str);
		if (fcntl(fd, F_GETFD) == -1)
		{
			ft_printf("\nError, %s is not set as file descriptor\n", c->right->token.str);
			return ((void *)1);
		}
		return (c->right->right);
	}
	ft_printf("\nError, file number execpted\n");
	return ((void *)1);
}

t_tree	*gand(t_process *p, t_tree *c)
{
	(void)p;
	if (fully_digit(c->right->token.str) == 0)
	{
		closefd[1] = ft_atoi(c->right->token.str);
		if (fcntl(closefd[1], F_GETFD) == -1)
		{
			ft_printf("\nError, %s is not set as file descriptor\n", c->right->token.str);
			return ((void *)1);
		}
		dup2(closefd[1], STDOUT_FILENO);
		return (c->right->right);
	}
	else
	{
		close(STDOUT_FILENO);
		if (ft_memcmp("-", c->right->token.str, ft_strlen(c->right->token.str)) == 0)
			return (c->right->right);
		else if ((closefd[1] = open(c->right->token.str, O_CREAT | O_TRUNC | O_WRONLY, 0755)) == -1)
			return ((void*)1);
		dup2(STDOUT_FILENO, closefd[1]);
	}
	return (c->right->right);
}

t_tree	*lessgreat(t_process *p, t_tree *c)
{
	(void)p;
	close(STDIN_FILENO);
	if ((closefd[0] = (open(c->right->token.str, O_RDONLY, 0755))) == -1)
		return ((void *)1);
	dup2(STDIN_FILENO, closefd[0]);
	if (c->previous == NULL)
	{
		close(STDOUT_FILENO);
		if ((closefd[1] = (open(c->right->token.str, O_CREAT | O_WRONLY, 0755))) == -1)
			return ((void *)1);
		dup2(STDOUT_FILENO, closefd[1]);
	}
	return (c->right->right);	
}

// t_tree	*clobber(t_process *p, t_tree *c)
// {
// 	// oublie
// 	(void)p;
// 	(void)c;
// 	return (c->right->right);
// }

t_tree	*ft_dgreat(t_process *p, t_tree *c)
{
	(void)p;
	close(STDOUT_FILENO);
	if ((closefd[1] = (open(c->right->token.str, O_APPEND | O_CREAT | O_WRONLY, 0755))) == -1)
		return ((void *)1);
	dup2(STDOUT_FILENO, closefd[1]);
	c = c->right->right;
	return (c);
}

t_tree	*ft_less(t_process *p, t_tree *c)
{
	(void)p;
	close(STDIN_FILENO);
	if ((closefd[0] = (open(c->right->token.str, O_RDONLY, 0755))) == -1)
		return ((void *)1);
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
	return (0);
}

t_tree	*modify_io(t_process *p, t_tree *clist)
{
	int	fd;

	fd = -1;
	if (fully_digit(clist->token.str) == 0)
		fd = ft_atoi(clist->token.str);
	if (fcntl(fd, F_GETFD) == -1)
	{
		if (((fd = open(clist->token.str, O_WRONLY, 0755))) == -1)
		{
			ft_printf("\nError, %s is not set as file descriptor\n", clist->token.str);
			return ((void *)1);
		}
	}
	else if (modify_fd(fd, clist->right, p) == -1)
		return ((void *)1);
	return (clist->right->right->right);
}