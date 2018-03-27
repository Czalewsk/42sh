/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:09:36 by thugo             #+#    #+#             */
/*   Updated: 2018/03/23 13:50:05 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ft_sh.h"

static void	access_retrieve(const char *path, char *stats)
{
	*stats |= (STATS_EXIST | STATS_EXEC);
	if (access(path, F_OK | X_OK))
	{
		if (errno == ENOENT)
			*stats &= ~STATS_EXIST;
		if (errno == EACCES)
			*stats &= ~STATS_EXEC;
	}
}

static void	stats_retrieve(const char *path, char *stats)
{
	struct stat	st;

	if (stat(path, &st))
		return ;
	*stats |= S_ISDIR(st.st_mode) * STATS_DIR;
}

char		stats_check(const char *path)
{
	char	stats;

	stats = 0;
	access_retrieve(path, &stats);
	if ((stats & STATS_EXIST))
		stats_retrieve(path, &stats);
	return (stats);
}

int			stats_filecmp(const char *p1, const char *p2)
{
	struct stat	st1;
	struct stat	st2;

	if (stat(p1, &st1) || stat(p2, &st2))
		return (0);
	if (st1.st_dev == st2.st_dev && st1.st_ino == st2.st_ino)
		return (1);
	return (0);
}
