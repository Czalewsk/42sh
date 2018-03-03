/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 23:46:36 by thugo             #+#    #+#             */
/*   Updated: 2017/04/11 14:27:11 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_TYPES_H
# define LIBUNIT_TYPES_H

# define FTYPE_FN 		1
# define FTYPE_FN_IO	2
# define FTYPE_EXE		3

# define GL_BUFF_SIZE	64

# include <sys/types.h>

typedef struct	s_ml_list
{
	void				*content;
	struct s_ml_list	*next;
}				t_ml_list;

typedef struct	s_unit_tests
{
	char			*name;
	t_ml_list		*launchers;
}				t_unit_tests;

typedef struct	s_unit_launcher
{
	char			*name;
	t_ml_list		*tests;
}				t_unit_launcher;

typedef struct	s_unit_exe
{
	char			*path;
	char			**argv;
	int				(*fn)(int, int, pid_t);
}				t_unit_exe;

typedef union	u_unit_fntypes
{
	int				(*fn)(void);
	int				(*fn_io)(int, int);
	t_unit_exe		exe;
}				t_unit_fntypes;

typedef struct	s_unit_test
{
	char			*name;
	int				ftype;
	t_unit_fntypes	f;
}				t_unit_test;

typedef struct	s_u_gl
{
	int				fd;
	char			buffer[GL_BUFF_SIZE + 1];
}				t_u_gl;

#endif
