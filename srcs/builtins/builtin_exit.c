/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 19:24:49 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/13 19:43:24 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			builtin_exit(t_process *p, int argc, char **argv, char **env)
{
	(void)p;
	(void)env;
	if (argc > 2)
		return (sh_error(1, 0, NULL, 1, "exit: too many arguments"));
	g_sh_exit = 1;
	return (ft_atoi(argc == 2 ? argv[1] : ""));
}
