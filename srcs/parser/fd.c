/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 19:44:57 by maastie           #+#    #+#             */
/*   Updated: 2018/03/27 15:45:48 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			sh_check_fd(char *str)
{
	int	ret;

	ret = ft_isint(str) ? ft_atoi(str) : -1;
	if (ret == -1 && ft_memcmp(str, "-", 1) == 0)
		return (-1);
	if (ret <= 10)
		return (ret);
	return (sh_error(-1, 0, NULL, 3, "Error in redirection, number ", str,
		" must be between 0 and 10\n"));
}

char		sh_great(char *left, char *right, char io_default, t_list **open_fd)
{
	int lfd;
	int rfd;

	if ((rfd = open(right, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		return (1);
	lfd = io_default ? 1 : sh_check_fd(left);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) < 0)
		return (-1);
	close(rfd);
	return (0);
}


char		sh_dgreat(char *left, char *right, char io_default,
		t_list **open_fd)
{
	int lfd;
	int rfd;

	if ((rfd= open(right, O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
		return (1);
	lfd = io_default ? 1 : sh_check_fd(left);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) < -1)
		return (-1);
	return (0);
}

char		sh_less(char *left, char *right, char io_default, t_list **open_fd)
{
	int lfd;
	int rfd;

	if ((rfd = open(right, O_RDONLY, 0644)) == -1)
		return (1);
	lfd = io_default ? 0 : sh_check_fd(left);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) == -1)
		return (-1);
	return (0);
}

char		sh_lessand(char *left, char *right, char io_default, t_list **open_fd)
{
	int lfd;
	int rfd;

	(void)open_fd;
	rfd = sh_check_fd(right);
	lfd = io_default ? 0 : sh_check_fd(left);
	if (rfd == -1)
		close(lfd);
	else if (dup2(rfd, lfd) == -1)
			return (-1);
	return (0);
}

char		sh_greatand(char	*left, char	*right, char io_default,
		t_list **open_fd)
{
	int lfd;
	int	rfd;

	(void)open_fd;
	rfd = sh_check_fd(right);
	lfd = io_default ? 1 : sh_check_fd(left);
	if (rfd == -1)
		close(lfd);
	else if (dup2(rfd, lfd) == -1)
		return (-1);
	return (0);
}

char		sh_lessgreat(char *left, char *right, char io_default,
		t_list **open_fd)
{
	int lfd;
	int rfd;

	if ((rfd = open(right, O_RDWR | O_CREAT, 0644)) == -1)
		return (1);
	if (io_default)
		lfd = 0;
	else
		lfd = sh_check_fd(left);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) == -1)
		return (-1);
	return (0);
}

char		sh_dless(char *left, char *right, char io_default,
		t_list **open_fd)
{
	t_list	*tmp_list;
	t_here	*tmph;
	int		ref_here;
	int		lfd;
	int		rfd;

	(void)right;
	if (!(tmp_list = g_here_list))
		return (0);
	tmph = tmp_list->content;
	ref_here = tmph->num;
	rfd = tmph->fd[0];
	close(tmph->fd[1]);
	while (tmp_list)
	{
		tmph = tmp_list->content;
		if (tmph->num != ref_here)
			break ;
		tmp_list = tmp_list->next;
		ft_lst_remove_index(&g_here_list, 0, NULL);
	}
	lfd = io_default ? 0 : sh_check_fd(left);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	dup2(rfd, lfd);
	close(rfd);
	return (0);
}
