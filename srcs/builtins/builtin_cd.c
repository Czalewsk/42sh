/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:20:02 by thugo             #+#    #+#             */
/*   Updated: 2018/03/15 01:44:27 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "ft_sh.h"

static char	*resolve_path(t_process *p, char **argv, char **env)
{
	char	*path;

	if (!*argv)
	{
		if (!(path = ft_getenv(env, "HOME")))
		{
			sh_error_bi(p->stderr, 0, 1, "cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (!ft_strcmp(*argv, "-"))
	{
		if (!(path = ft_getenv(env, "OLDPWD")))
		{
			sh_error_bi(p->stderr, 0, 1, "cd: OLDPWD not set\n");
			return (0);
		}
	}
	else
		path = *argv;
	return (path);
}

static char	*get_lpath(char *path, char **env)
{
	char	**splitpath;
	char	*lpath;
	int		i;

	splitpath = ft_strsplit(path, '/');
	if (path[0] == '/')
		lpath = ft_strnew(0);
	else if (ft_getenv(env, "PWD"))
		lpath = ft_strdup(ft_getenv(env, "PWD"));
	else
		lpath = getcwd(NULL, 0);
	i = -1;
	while (splitpath[++i])
	{
		if (!ft_strcmp(splitpath[i], "..") && ft_strlen(lpath) > 1)
			lpath = ft_strnfdup(lpath, ft_strrchr(lpath, '/') - lpath);
		else if (ft_strcmp(splitpath[i], ".") && ft_strcmp(splitpath[i], ".."))
			lpath = ft_strjoin_free(lpath, ft_strjoin("/", splitpath[i]), 2);
	}
	free_tab2d((char ***)&splitpath);
	return ((lpath = ft_strlen(lpath) ? lpath : ft_strjoin_free(lpath, "/",
		0)));
}

static int	can_change_dir(t_process *p, char *path)
{
	char	stats;

	stats = stats_check(path);
	if (ft_strlen(path) && (!(stats & STATS_EXIST) || !(stats & STATS_EXEC) ||
		!(stats & STATS_DIR)))
	{
		if (!(stats & STATS_EXIST))
			sh_error_bi(p->stderr, 0, 3, "cd: no such file or directory: ",
				path, "\n");
		else if (!(stats & STATS_DIR))
			sh_error_bi(p->stderr, 0, 3, "cd: not a directory: ", path, "\n");
		else if (!(stats & STATS_EXEC))
			sh_error_bi(p->stderr, 0, 3, "cd: permission denied: ", path,
				"\n");
		return (0);
	}
	return (1);
}

static int	changedir(t_process *p, char *path, char *cmd, char **env)
{
	char	cwd[MAXPATHLEN];

	if (!can_change_dir(p, cmd ? cmd : path))
		return (1);
	if (!ft_getenv(env, "PWD"))
		env_set("OLDPWD", getcwd(cwd, MAXPATHLEN), ENV_LOCAL);
	else
		env_set("OLDPWD", ft_getenv(env, "PWD"), ENV_LOCAL);
	cwd_change(path);
	return (0);
}

int			builtin_cd(t_process *p, int argc, char **argv, char **env)
{
	char	*path;
	char	*lpath;
	char	*options;
	int		index;
	int		ret;

	if ((index = ft_getopt(argc, argv, "LP", &options)) == -1)
	{
		free(options);
		return (sh_error_bi(p->stderr, EXIT_FAILURE, 3, "cd: bad option: -",
			options, "\n"));
	}
	if (!(path = resolve_path(p, argv + index, env)))
	{
		free(options);
		return (1);
	}
	if (ft_strchr(options, 'P'))
		ret = changedir(p, path, NULL, env);
	else
	{
		lpath = get_lpath(path, env);
		ret = changedir(p, lpath, path, env);
		free(lpath);
	}
	free(options);
	return (ret);
}
