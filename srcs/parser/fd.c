/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 19:44:57 by maastie           #+#    #+#             */
/*   Updated: 2018/03/26 20:18:01 by czalewsk         ###   ########.fr       */
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

char		sh_great(char *left, char *right, char io_default)
{
	int lfd;
	int rfd;

	if ((rfd= open(right, O_CREAT | O_TRUNC | O_WRONLY, 0755)) == -1)
		return (1);
	if (io_default)
		lfd = 1;
	else
		lfd = sh_check_fd(left);
	dup2(rfd, lfd);
	return (0);
}


char		sh_dgreat(char *left, char *right, char io_default)
{
	int lfd;
	int rfd;

	if ((rfd= open(right, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1)
		return (1);
	if (io_default)
		lfd = 1;
	else
		lfd = sh_check_fd(left);
	dup2(rfd, lfd);
	return (0);
}

char		sh_less(char *left, char *right, char io_default)
{
	int lfd;
	int rfd;

	if ((rfd= open(right, O_RDONLY, 0755)) == -1)
		return (1);
	if (io_default)
		lfd = 0;
	else
		lfd = sh_check_fd(left);
	if (dup2(rfd, lfd) == -1)
		return (1);
	return (0);
}

char		sh_lessand(char *left, char *right, char io_default)
{
	int lfd;
	int rfd;

	rfd = sh_check_fd(right);
	if (io_default)
		lfd = 0;
	else
		lfd = sh_check_fd(left);
	if (rfd == -1)
		close(lfd);
	else if (dup2(dup(rfd), lfd) == -1)
		return (1);
	return (0);
}

char		sh_greatand(char	*left, char	*right, char io_default)
{
	int lfd;
	int	rfd;

	rfd = sh_check_fd(right);
	if (io_default)
		lfd = 1;
	else
		lfd = sh_check_fd(left);
	DEBUG("left=[%s] | lfd=%d|\n", left, lfd);
	DEBUG("right=[%s] | rfd=%d|\n", right, rfd);
	if (rfd == -1)
		close(lfd);
	else if (dup2(dup(rfd), lfd) == -1)
		return (1);
	return (0);
}

char		sh_lessgreat(char *left, char *right, char io_default)
{
	int lfd;
	int rfd;

	if ((rfd= open(right, O_RDWR | O_CREAT, 0755)) == -1)
		return (1);
	if (io_default)
		lfd = 0;
	else
		lfd = sh_check_fd(left);
	if (dup2(dup(rfd), lfd) == -1)
		return (1);
	return (0);
}

