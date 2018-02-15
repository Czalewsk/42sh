/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 01:02:21 by thugo             #+#    #+#             */
/*   Updated: 2017/03/30 03:04:01 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libunit_types.h"

/*
** 	Initialise la serie de tests
*/

t_unit_tests	*unit_init(char *name)
{
	t_unit_tests	*tests;

	if (!(tests = (t_unit_tests *)malloc(sizeof(t_unit_tests))))
		exit(EXIT_FAILURE);
	memset(tests, 0, sizeof(t_unit_tests));
	if (!(tests->name = strdup(name)))
		exit(EXIT_FAILURE);
	return (tests);
}
