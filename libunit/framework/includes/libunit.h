/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:06:47 by thugo             #+#    #+#             */
/*   Updated: 2017/04/05 06:58:22 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_H
# define LIBUNIT_H

# include <libunit_types.h>

t_unit_tests	*unit_init(char *name);

void			unit_register_launcher(t_unit_tests *tests, char *name,
					void (*f)(t_unit_launcher *));

void			unit_register_fn(t_unit_launcher *launcher, char *name,
					int (*f)(void));

void			unit_register_fn_io(t_unit_launcher *launcher, char *name,
					int (*f)(int, int));

void			unit_register_exe(t_unit_launcher *launcher, char *name,
					char *path, char **argv, int (*f)(int, int, pid_t));

int				unit_launch_tests(t_unit_tests *tests);

#endif
