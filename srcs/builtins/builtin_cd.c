/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:20:02 by thugo             #+#    #+#             */
/*   Updated: 2018/03/14 15:20:34 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char	*resolve_path(int argc, char **argv, int index)
{
	char	*path;

	if (index >= argc)
	{
		if (!(path = ft_getenv(
	}
}

int			builtin_cd(t_process *p)
{
	char	*options;
	int		i;
	char	*path;
	char	*lpath;

	if ((i = ft_getopt(ft_tab2dlen(p->argv), p->argv, "LP", &options)) == -1)
		return (sh_error_bi(...));
	if (!(path = resolve_path(ft_tab2dlen(p->argv), p->argv, index)))
		return (EXIT_FAILURE);
	if (ft_strchr(options, 'P'))
		ret = changedir(path, NULL);
	else
	{
		lpath = get_lpath(path);
		ret = changedir(lpath, path);
		free(lpath);
	}
	free(options);
	return (ret);
}
