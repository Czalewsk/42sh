/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 22:17:51 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 02:58:34 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libunit.h"
#include "launchers.h"
#include "ft_sh.h"

t_sh	g_sh;

int	main(void)
{
	t_unit_tests		*tests;

	g_sh.env = NULL;
	tests = unit_init(" - - - - - - 42sh - - - - - - ");
	unit_register_launcher(tests, "Expansions", expansions_launcher);
	if (!unit_launch_tests(tests))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
