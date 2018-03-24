/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 08:29:39 by thugo             #+#    #+#             */
/*   Updated: 2018/03/24 17:11:46 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	convert_tological(char **curpath)
{
	char	*cur;
	char	*comp_start;

	cur = *curpath + 1;
	comp_start = *curpath;
	ft_printf("Enter: %s\n", *curpath);
	while (*cur)
	{
		if (*cur == '/' || (!*(cur + 1) && ++cur))
		{
			printf("Comp: %.*s\n", (int)(cur - comp_start - 1), comp_start + 1);
			printf("Cur: %s\n", cur);
			if (cur - comp_start == 1){ft_printf("CC1\n");
				ft_strcpy(comp_start, cur--);}
			if (!ft_strncmp(comp_start + 1, ".", cur - comp_start - 1)){ft_printf("CC2\n");
				(ft_strcpy(comp_start, cur) && (cur -= 3));}
			if (!*cur)
				--cur;
			comp_start = cur;
		}
		++cur;
	}
	return (0);
}

/*
**	Return:
**		2: HOME
**		1: OLDPWD
**		0: Argv
*/

static int	set_curpath(char **argv, char **env, char **curpath)
{
	char	*first;

	*curpath = NULL;
	if ((argv[0] && !ft_strcmp(argv[0], "-")) || !argv[0])
	{
		*curpath = ft_strdup(ft_getenv(env, !argv[0] ? "HOME" : "OLDPWD"));
		return (!argv[0] ? 2 : 1);
	}
	first = ft_strchr(argv[0], '/');
	if (!first)
		first = argv[0] + ft_strlen(argv[0]);
	if ((argv[0][0] == '/' || (!ft_strncmp(argv[0], "." ,first - argv[0]) ||
			!ft_strncmp(argv[0], "..", first - argv[0]))))
		*curpath = ft_strdup(argv[0]);
	else if (!*curpath)
		*curpath = find_cdpath(argv[0], ft_getenv(env, "CDPATH"));
	*curpath = *curpath ? *curpath : ft_strdup(argv[0]);
	return (0);
}

int			builtin_cd(t_process *p, int argc, char **argv, char **env)
{
	char	opt[3];
	char	*curpath;
	int		index;
	int		ret;

	if ((index = ft_getopt_buf(argc, argv, "LP", opt)) == -1)
		return (sh_error_bi(p->stderr, 1, 3, "cd: bad option: -", opt, "\n"));
	ret = set_curpath(argv + index, env, &curpath);
	if (!curpath && ret == 1)
		return (sh_error_bi(p->stderr, 1, 1, "cd: $OLDPWD not set\n"));
	else if (!curpath && ret == 2)
		return (sh_error_bi(p->stderr, 1, 1, "cd: $HOME not set\n"));
	if (!ft_strchr(opt, 'P'))
	{
		if (curpath[0] != '/')
			curpath = g_sh.cwd[ft_strlen(g_sh.cwd) - 1] == '/' ?
				ft_strjoin_free(g_sh.cwd, curpath, 1) :
				ft_strjoin_free(g_sh.cwd, ft_strjoin_free("/", curpath, 1), 1);
		convert_tological(&curpath);
	}
	ft_printf("Curpath: %s\n", curpath);
	free(curpath);
	return (0);
}
