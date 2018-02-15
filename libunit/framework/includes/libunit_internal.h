/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 20:02:07 by thugo             #+#    #+#             */
/*   Updated: 2017/04/04 22:40:10 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_INTERNAL_H
# define LIBUNIT_INTERNAL_H

# define EXIT_BADEXE 3

void	print_header(char *name);
void	print_test(int status, char *name);
void	print_total(int valid, int total);

#endif
