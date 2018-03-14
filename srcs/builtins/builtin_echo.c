/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:28:50 by bviala            #+#    #+#             */
/*   Updated: 2018/03/14 15:20:37 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			builtin_echo(t_process *p, int argc, char **argv, char **env)
{
	int	nonl;

	(void)argc;
	(void)env;
	nonl = 0;
	argv++;
	if (*argv && !ft_strcmp(*argv, "-n"))
	{
		argv++;
		nonl = 1;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, p->stdout);
		argv++;
		if (*argv)
			ft_putchar_fd(' ', p->stdout);
	}
	if (!nonl)
		ft_putchar_fd('\n', p->stdout);
	return (EXIT_SUCCESS);
}
