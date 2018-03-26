/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 08:29:39 by thugo             #+#    #+#             */
/*   Updated: 2018/03/26 18:27:34 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "ft_sh.h"

static int	change_dir(t_process *p, char *path, int logic, int print)
{
	char	stats;

	stats = stats_check(path);
	if ((stats & (STATS_EXIST | STATS_EXEC | STATS_DIR)) !=
		(STATS_EXIST | STATS_EXEC | STATS_DIR))
	{
		if (!(stats & STATS_EXIST))
			sh_error_bi(p->stderr, 0, 3, "cd: no such file or directory: ",
				path, "\n");
		else if (!(stats & STATS_DIR))
			sh_error_bi(p->stderr, 0, 3, "cd: not a directory: ", path, "\n");
		else if (!(stats & STATS_EXEC))
			sh_error_bi(p->stderr, 0, 3, "cd: permission denied: ", path,
				"\n");
		return (EXIT_FAILURE);
	}
	env_set("OLDPWD", g_sh.cwd, ENV_GLOBAL);
	cwd_change(path, logic);
	if (print)
		ft_putendl_fd(path, p->stdout);
	return (EXIT_SUCCESS);
}

static char	*ft_strnrchr(const char *s, char c, size_t size)
{
	char	*save;
	int		i;

	save = NULL;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	i = -1;
	while (s[++i] && i < (int)size)
		if (s[i] == c)
			save = (char *)s + i;
	return (save);
}

static void	convert_tological(char *curpath)
{
	char	*cur;
	char	*comp_start;

	cur = curpath + 1;
	comp_start = curpath;
	while (*cur)
	{
		if (*cur == '/' || (!*(cur + 1) && ++cur))
		{
			if (cur - comp_start == 1)
				ft_strcpy(comp_start, cur--);
			else if (!ft_strncmp(comp_start + 1, ".", cur - comp_start - 1))
				(ft_strcpy(comp_start, cur) && (cur -= 2));
			else if (!ft_strncmp(comp_start + 1, "..", cur - comp_start - 1))
				cur = ft_strcpy(comp_start != curpath ? ft_strnrchr(curpath,
					'/', comp_start - (curpath + 1)) : comp_start, cur);
			curpath = *curpath ? curpath : ft_strcpy(curpath, "/");
			if (!*cur)
				--cur;
			comp_start = cur;
		}
		++cur;
	}
	if (cur != curpath && --cur != curpath && *cur == '/')
		*cur = '\0';
}

/*
**	Return:
**		3: CDPATH
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
	if ((argv[0][0] == '/' || (!ft_strncmp(argv[0], ".", first - argv[0]) ||
			!ft_strncmp(argv[0], "..", first - argv[0]))))
		*curpath = ft_strdup(argv[0]);
	else if (!*curpath && (*curpath = find_cdpath(argv[0],
			ft_getenv(env, "CDPATH"))))
		return (3);
	*curpath = ft_strdup(argv[0]);
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
	else if (!curpath)
		return (sh_error_bi(p->stderr, 1, 1, "cd: $HOME not set\n"));
	if (!ft_strchr(opt, 'P'))
	{
		if (curpath[0] != '/')
			curpath = g_sh.cwd[ft_strlen(g_sh.cwd) - 1] == '/' ?
				ft_strjoin_free(g_sh.cwd, curpath, 1) :
				ft_strjoin_free(g_sh.cwd, ft_strjoin_free("/", curpath, 1), 1);
		convert_tological(curpath);
	}
	ret = change_dir(p, curpath, !ft_strchr(opt, 'P'), ret);
	free(curpath);
	return (ret);
}
