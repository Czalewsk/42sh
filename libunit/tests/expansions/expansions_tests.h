/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_tests.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 07:19:54 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 07:09:08 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_TESTS_H
# define EXPANSIONS_TESTS_H

int		expansions_parameters_noexpand(void);
int		expansions_parameters_basic(void);
int		expansions_parameters_mulexpand(void);
int		expansions_parameters_empty(void);
int		expansions_parameters_catexpand(void);
int		expansions_parameters_escape(void);
int		expansions_parameters_ifs(void);
int		expansions_parameters_ifsassign(void);
int		expansions_parameters_ifsunset(void);
int		expansions_parameters_advanced(void);
int		expansions_tilde_basic(void);
int		expansions_tilde_escape(void);
int		expansions_tilde_noexpand(void);
int		expansions_tilde_assign(void);
int		expansions_tilde_nohome(void);
int		expansions_tilde_badlogin(void);
int		expansions_tilde_slash(void);
int		expansions_tilde_param(void);
int		expansions_tilde_paramslash(void);

#endif
