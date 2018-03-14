/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:05:03 by bviala            #+#    #+#             */
/*   Updated: 2018/03/13 22:17:58 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_a_bin(const char *path)
{
	struct stat buf;

	if (stat(path, &buf))
		return (0);
	if (S_ISREG(buf.st_mode))
		return (S_IXUSR & buf.st_mode);
	return (0);
}

int	ft_is_a_reg_file(const char *path)
{
	struct stat buf;

	stat(path, &buf);
	return (S_ISREG(buf.st_mode));
}

int	ft_is_a_file(const char *path)
{
	struct stat buf;

	stat(path, &buf);
	if (S_ISREG(buf.st_mode) || S_ISBLK(buf.st_mode) || S_ISCHR(buf.st_mode)
			|| S_ISFIFO(buf.st_mode) || S_ISLNK(buf.st_mode)
			|| S_ISSOCK(buf.st_mode) || S_ISWHT(buf.st_mode))
		return (1);
	return (0);
}

int	ft_is_a_dir(const char *path)
{
	struct stat buf;

	ft_bzero(&buf, sizeof(buf));
	stat(path, &buf);
	return (S_ISDIR(buf.st_mode));
}
