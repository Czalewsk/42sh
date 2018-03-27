/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cdpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:12:04 by thugo             #+#    #+#             */
/*   Updated: 2018/03/23 16:24:40 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*find_cdpath(char *find, char *cdpath)
{
	char	**pathsplit;
	char	*fullpath;
	int		i;

	if (!find || !cdpath || !(pathsplit = ft_strsplit(cdpath, ':')))
		return (NULL);
	i = -1;
	while (pathsplit[++i])
	{
		fullpath = NULL;
		if (pathsplit[i][ft_strlen(pathsplit[i]) - 1] != '/')
			fullpath = ft_strjoin(pathsplit[i], "/");
		fullpath = fullpath ? ft_strjoin_free(fullpath, find, 0) :
			ft_strjoin(pathsplit[i], find);
		if (stats_check(fullpath) & (STATS_EXIST | STATS_DIR))
		{
			free_tab2d(&pathsplit);
			return (fullpath);
		}
		free(fullpath);
	}
	free_tab2d(&pathsplit);
	return (NULL);
}
