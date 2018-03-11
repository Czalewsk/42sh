/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 08:31:57 by thugo             #+#    #+#             */
/*   Updated: 2018/03/09 09:43:23 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	print_env(t_process *p, char **env)
{
	while (*env)
	{
		ft_putendl_fd(*env, p->stdout);
		++env;
	}
}

int			builtin_setenv(t_process *p, int argc, char **argv, char **env)
{
	if (argc < 2)
		print_env(p, env);
	else if (argc > 3)
		return (sh_error_bi(p->stderr, EXIT_FAILURE, 1,
			"setenv: Too many arguments.\n"));
	else
	{
		if (!ft_isposixname(argv[1]))
		{
			return (sh_error_bi(p->stderr, EXIT_FAILURE, 1,
				"setenv: Variable name must begin with a letter.\n"));
		}
		env_set(argv[1], argc == 3 ? argv[2] : "", ENV_GLOBAL);
	}
	return (EXIT_SUCCESS);
}
