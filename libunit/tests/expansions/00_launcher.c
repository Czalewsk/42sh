/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 21:56:28 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 21:06:47 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include "expansions_tests.h"

void	expansions_launcher(t_unit_launcher *launcher)
{
	unit_register_fn(launcher, "Parameters no expand", 
		expansions_parameters_noexpand);
	unit_register_fn(launcher, "Parameters basic",
			expansions_parameters_basic);
	unit_register_fn(launcher, "Parameters multi expand",
			expansions_parameters_mulexpand);
	unit_register_fn(launcher, "Parameters empty",
			expansions_parameters_empty);
	unit_register_fn(launcher, "Parameters concat expand",
			expansions_parameters_catexpand);
	unit_register_fn(launcher, "Parameters escape",
			expansions_parameters_escape);
	unit_register_fn(launcher, "Parameters ifs",
			expansions_parameters_ifs);
	unit_register_fn(launcher, "Parameters ifs assign",
			expansions_parameters_ifsassign);
	unit_register_fn(launcher, "Parameters ifs unset",
			expansions_parameters_ifsunset);
	unit_register_fn(launcher, "Parameters advanced",
			expansions_parameters_advanced);
}
