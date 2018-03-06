/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 23:24:26 by maastie           #+#    #+#             */
/*   Updated: 2018/03/03 17:36:04 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		check_built_in(t_process *p)
{
	if (ft_memcmp(p->argv[0], "env", 3) == 0)
		return (0);
	else if (ft_memcmp(p->argv[0], "cd", 2) == 0)
		return (0);
	else if (ft_memcmp(p->argv[0], "setenv", 6) == 0)
		return (0);
	else if (ft_memcmp(p->argv[0], "unsetenv", 8) == 0)
		return (0);
	else if (ft_memcmp(p->argv[0], "echo", 5) == 0)
		return (0);
	else if (ft_memcmp(p->argv[0], "exit", 5) == 0)
		return (0);
	else if (ft_memcmp(p->argv[0], "fg", 2) == 0)
		return (0);
	else if (ft_memcmp(p->argv[0], "bg", 2) == 0)
		return (0);
	else if (ft_memcmp(p->argv[0], "jobs", 3) == 0)
		return (0);
	return (-1);
}

int		do_built_in(t_process *p)
{
	if (ft_memcmp(p->argv[0], "fg", 3) == 0)
		return (g_sh.exitstatus = (bt_fg(&(p->argv[1]))));
	if (ft_memcmp(p->argv[0], "bg", 3) == 0)
		return (g_sh.exitstatus = (bt_bg(&(p->argv[1]))));
	if (ft_memcmp(p->argv[0], "jobs", 3) == 0)
		return (g_sh.exitstatus = (bt_jobs(&(p->argv[1]))));
	return (0);
	// if (ft_memcmp(p->argv[0], "env", 3) == 0)
	// 	return (g_sh.exitstatus = (ft_env()));
	// else if (ft_memcmp(p->argv[0], "cd", 2) == 0)
	// 	return (g_sh.exitstatus = (ft_cd()));
	// else if (ft_memcmp(p->argv[0], "setenv", 6) == 0)
	// 	return (g_sh.exitstatus = (ft_setenv()));
	// else if (ft_memcmp(p->argv[0], "unsetenv", 8) == 0)
	// 	return (g_sh.exitstatus = (ft_unsetenv()));
	// else if (ft_memcmp(p->argv[0], "echo", 5) == 0)
	// 	return (g_sh.exitstatus = (ft_echo()));
	// else if (ft_memcmp(p->argv[0], "exit", 5) == 0)
	// 	return (g_sh.exitstatus = (ft_exit()));
	// return (-1);
}
