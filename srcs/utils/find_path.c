/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 11:15:43 by thugo             #+#    #+#             */
/*   Updated: 2018/03/23 10:49:41 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*find_path(char *name, char *path)
{
	char	**pathsplit;
	char	*fullpath;
	int		i;

	if (!name || !(pathsplit = ft_strsplit(path, ':')))
		return (NULL);
	i = -1;
	while (pathsplit[++i])
	{
		fullpath = NULL;
		if (pathsplit[i][ft_strlen(pathsplit[i]) - 1] != '/')
			fullpath = ft_strjoin(pathsplit[i], "/");
		fullpath = fullpath ? ft_strjoin_free(fullpath, name, 0) :
			ft_strjoin(pathsplit[i], name);
		if (ft_is_a_bin(fullpath))
		{
			free_tab2d(&pathsplit);
			return (fullpath);
		}
		ft_strdel(&fullpath);
	}
	free_tab2d(&pathsplit);
	return (NULL);
}
