/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 12:34:48 by maastie           #+#    #+#             */
/*   Updated: 2018/03/28 12:34:49 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		sh_great(t_fd *test_fd, t_list **open_fd)
{
	int		lfd;
	int		rfd;

	if ((rfd = open(test_fd->right_str,
		O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
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
	int		lfd;
	int		rfd;

	if ((rfd = open(test_fd->right_str,
		O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
		return (1);
	lfd = test_fd->io_default ? 1 : sh_check_fd(test_fd->left_str);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) < -1)
		return (-1);
	return (0);
}

char		sh_less(t_fd *test_fd, t_list **open_fd)
{
	int		lfd;
	int		rfd;

	if ((rfd = open(test_fd->right_str, O_RDONLY, 0644)) == -1)
		return (1);
	lfd = test_fd->io_default ? 0 : sh_check_fd(test_fd->left_str);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	if (dup2(rfd, lfd) == -1)
		return (-1);
	return (0);
}
