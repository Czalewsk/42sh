/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_tests.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 07:19:54 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 20:45:02 by thugo            ###   ########.fr       */
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

#endif
