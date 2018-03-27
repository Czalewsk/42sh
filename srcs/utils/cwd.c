/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:58:08 by thugo             #+#    #+#             */
/*   Updated: 2018/03/25 20:03:27 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	try(char *path)
{
	char	stats;

	sh_error(0, 0, NULL, 3, "Trying to start from \"", path, "\"\n");
	stats = stats_check(path);
	if ((stats & STATS_EXIST) && (stats & STATS_EXEC) && (stats & STATS_DIR))
	{
		cwd_change(path, 1);
		return (1);
	}
	return (0);
}

void		cwd_init(void)
{
	char	stats;
	char	*home;

	stats = 0;
	if ((g_sh.cwd = getcwd(NULL, 0)))
		stats = stats_check(g_sh.cwd);
	if (!g_sh.cwd || !(stats & STATS_EXEC) || !(stats & STATS_EXIST))
	{
		if (!(stats & STATS_EXIST))
			sh_error(0, 0, NULL, 1, "No such file or directory\n");
		else
			sh_error(0, 0, NULL, 1, "Permission denied\n");
		if ((home = env_get("HOME")) && try(home))
			return ;
		else if (try("/"))
			return ;
		g_sh_exit = 1;
		return ;
	}
	if (!stats_filecmp(g_sh.cwd, env_get("PWD")))
		env_set("PWD", g_sh.cwd, ENV_GLOBAL);
	chdir(g_sh.cwd);
}

void		cwd_change(const char *path, int logic)
{
	chdir(path);
	if (g_sh.cwd)
		free(g_sh.cwd);
	if (logic)
	{
		env_set("PWD", path, ENV_GLOBAL);
		if (!(g_sh.cwd = ft_strdup(path)))
			exit(EXIT_FAILURE);
	}
	else
	{
		g_sh.cwd = getcwd(NULL, 0);
		if (g_sh.cwd)
			env_set("PWD", g_sh.cwd, ENV_GLOBAL);
	}
}

void		cwd_destroy(void)
{
	free(g_sh.cwd);
}
