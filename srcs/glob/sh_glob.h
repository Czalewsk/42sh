/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:54:36 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/12 14:00:38 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SH_GLOB_H
# define __SH_GLOB_H

# include "libft.h"

typedef struct	s_brace_exp
{
	char	*pre;
	char	*post;
	t_ldl	word;
}				t_brace_exp;

char	brace_valide_type(char **curs, char **begin, char **end);

#endif