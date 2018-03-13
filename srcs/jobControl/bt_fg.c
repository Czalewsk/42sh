/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:08:50 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 19:05:18 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int	bt_fg(t_process *p, int size, char **arg, char **env)
{
	t_job	*tmp;

	(void)env;
	(void)p;
	(void)size;
	tmp = get_job(arg[1]);
	if (tmp == NULL)
	{
		if (*arg == NULL)
			sh_error(0, 0, NULL, 1, "fg: current: no such job\n");
		else
			sh_error(0, 0, NULL, 3, "fg: ", *arg, ": no such job\n");
		return (1);
	}
	printf("%s\n", tmp->command);
	continue_job(tmp, 1);
	return (0);
}