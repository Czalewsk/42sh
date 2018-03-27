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

char		sh_great(t_fd *test_fd, t_list **open_fd)
{
	int lfd;
	int rfd;

	if ((rfd = open(test_fd->right_str, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		return (1);
	lfd = test_fd->io_default ? 1 : sh_check_fd(test_fd->left_str);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) < 0)
		return (-1);
	close(rfd);
	return (0);
}


char		sh_dgreat(t_fd *test_fd, t_list **open_fd)
{
	int lfd;
	int rfd;

	if ((rfd = open(test_fd->right_str, O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
		return (1);
	lfd = test_fd->io_default ? 1 : sh_check_fd(test_fd->left_str);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) < -1)
		return (-1);
	return (0);
}

char		sh_less(t_fd *test_fd, t_list **open_fd)
{
	int lfd;
	int rfd;

	if ((rfd = open(test_fd->right_str, O_RDONLY, 0644)) == -1)
		return (1);
	lfd = test_fd->io_default ? 0 : sh_check_fd(test_fd->left_str);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) == -1)
		return (-1);
	return (0);
}

char		sh_lessand(t_fd *test_fd, t_list **open_fd)
{
	int lfd;
	int rfd;

	(void)open_fd;
	rfd = sh_check_fd(test_fd->right_str);
	lfd = test_fd->io_default ? 0 : sh_check_fd(test_fd->left_str);
	if (rfd == -1)
		close(lfd);
	else if (dup2(rfd, lfd) == -1)
			return (-1);
	close(rfd);
	return (0);
}

char		sh_greatand(t_fd *test_fd, t_list **open_fd)
{
	int lfd;
	int	rfd;

	(void)open_fd;
	rfd = sh_check_fd(test_fd->right_str);
	lfd = test_fd->io_default ? 1 : sh_check_fd(test_fd->left_str);
	if (rfd == -1)
		close(lfd);
	else if (dup2(rfd, lfd) == -1)
		return (-1);
	return (0);
}

char		sh_lessgreat(t_fd *test_fd, t_list **open_fd)
{
	int lfd;
	int rfd;

	if ((rfd = open(test_fd->right_str, O_RDWR | O_CREAT, 0644)) == -1)
		return (1);
	if (test_fd->io_default)
		lfd = 0;
	else
		lfd = sh_check_fd(test_fd->left_str);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) == -1)
		return (-1);
	return (0);
}

char		sh_dless(t_fd *test_fd, t_list **open_fd)
{
	int		lfd;

	lfd = test_fd->io_default ? 0 : sh_check_fd(test_fd->left_str);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(test_fd->here_doc, lfd) == -1)
		DEBUG("here_doc = %d | lfd = %d why ? %s\n ", test_fd->here_doc, lfd, strerror(errno));
	close(test_fd->here_doc);
//	ft_lst_remove_index(&g_here_list, 0, NULL);
	return (0);
}
