/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:28:00 by thugo             #+#    #+#             */
/*   Updated: 2018/03/11 20:24:45 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	posix_name_err(t_process *p, char *name)
{
	return (sh_error_bi(p->stderr, EXIT_FAILURE, 3, "export: '",
		name, "': not a valid name\n"));
}

static void	print_variables(t_process *p, char **env)
{
	int		i;
	char	*sep;

	i = -1;
	while (env[++i])
	{
		sep = ft_strchr(env[i], '=');
		ft_putstr_fd("export ", p->stdout);
		write(p->stdout, env[i], sep - env[i]);
		ft_putstr_fd("='", p->stdout);
		ft_putstr_fd(sep + 1, p->stdout);
		ft_putstr_fd("'\n", p->stdout);
	}
}

static int	export_variables(t_process *p, char **argv, char **env)
{
	char	*sep;
	char	*name;
	char	*value;

	while (*argv)
	{
		name = NULL;
		value = NULL;
		if ((sep = ft_strchr(*argv, '=')))
		{
			name = ft_strndup(*argv, sep - *argv);
			value = sep + 1;
		}
		if (!ft_isposixname(name ? name : *argv))
			posix_name_err(p, name ? name : *argv);
		if (value)
			env_set(name, value, ENV_GLOBAL);
		else if ((sep = ft_getenv(env, name ? name : *argv)))
			env_set(name ? name : *argv, sep, ENV_GLOBAL);
		else
			env_settype(name ? name : *argv, ENV_GLOBAL);
		free(name);
		++argv;
	}
	return (EXIT_SUCCESS);
}

int			builtin_export(t_process *p, int argc, char **argv, char **env)
{
	int		id;
	char	*res;

	if ((id = ft_getopt(argc, argv, "p", &res)) == -1)
	{
		ft_putstr_fd("export: -", p->stderr);
		ft_putchar_fd(*res, p->stderr);
		ft_putstr_fd(": invalid option\n", p->stderr);
		free(res);
		return (EXIT_FAILURE);
	}
	if ((ft_strchr(res, 'p') || !*res) && argc == id)
		print_variables(p, env);
	else
		export_variables(p, argv + id, env);
	free(res);
	return (EXIT_SUCCESS);
}
