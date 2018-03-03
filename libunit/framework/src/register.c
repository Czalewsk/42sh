/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:51:43 by thugo             #+#    #+#             */
/*   Updated: 2017/04/05 07:01:58 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libunit.h"
#include "minilib.h"

/*
**	Enregistrement d'un launcher et stockage de tout les tests dans celui-ci.
*/

void	unit_register_launcher(t_unit_tests *tests, char *name,
		void (*f)(t_unit_launcher *))
{
	t_unit_launcher	launcher;
	t_ml_list		*new;

	if (!tests || !name || !f)
		return ;
	memset(&launcher, 0, sizeof(t_unit_launcher));
	if (!(launcher.name = strdup(name)))
		exit(EXIT_FAILURE);
	f(&launcher);
	if (!(new = ml_lstnew(&launcher, sizeof(t_unit_launcher))))
		exit(EXIT_FAILURE);
	ml_lstpush(&(tests->launchers), new);
}


/*
**	Enregistrement d'une fonction de test standard sans redirection de stdin
**	et stdout.
*/

void	unit_register_fn(t_unit_launcher *launcher, char *name, int (*f)(void))
{
	t_unit_test	test;
	t_ml_list	*new;

	if (!launcher || !name || !f)
		return ;
	memset(&test, 0, sizeof(t_unit_test));
	if (!(test.name = strdup(name)))
		exit(EXIT_FAILURE);
	test.ftype = FTYPE_FN;
	test.f.fn = f;
	if (!(new = ml_lstnew(&test, sizeof(t_unit_test))))
		exit(EXIT_FAILURE);
	ml_lstpush(&(launcher->tests), new);
}

/*
**	Enregistrement d'une fonction de test avec un pipe de stdin et stdout.
*/

void	unit_register_fn_io(t_unit_launcher *launcher, char *name,
		int (*f)(int, int))
{
	
	t_unit_test	test;
	t_ml_list	*new;

	if (!launcher || !name || !f)
		return ;
	memset(&test, 0, sizeof(t_unit_test));
	if (!(test.name = strdup(name)))
		exit(EXIT_FAILURE);
	test.ftype = FTYPE_FN_IO;
	test.f.fn_io = f;
	if (!(new = ml_lstnew(&test, sizeof(t_unit_test))))
		exit(EXIT_FAILURE);
	ml_lstpush(&(launcher->tests), new);
}

/*
**	Enregistrement d'un programme avec redirection de stdin et stdout.
*/

void	unit_register_exe(t_unit_launcher *launcher, char *name, char *path,
		char **argv, int (*f)(int, int, pid_t))
{
	t_unit_test	test;
	t_ml_list	*new;

	if (!launcher || !name || !path)
		return ;
	memset(&test, 0, sizeof(t_unit_test));
	test.name = strdup(name);
	test.ftype = FTYPE_EXE;
	if (!(test.f.exe.path = strdup(path)))
		exit(EXIT_FAILURE);
	if (!(test.f.exe.argv = ml_nulltabdup(argv)))
		exit(EXIT_FAILURE);
	test.f.exe.fn = f;
	if (!(new = ml_lstnew(&test, sizeof(t_unit_test))))
		exit(EXIT_FAILURE);
	ml_lstpush(&(launcher->tests), new);
}
