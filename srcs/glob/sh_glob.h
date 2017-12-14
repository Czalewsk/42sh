/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:54:36 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 04:38:40 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SH_GLOB_H
# define __SH_GLOB_H

# include "ft_sh.h"
# include "libft.h"

# define GLOB_CHECK_CLOSE(str, x) ((*(str + x / 8)) & (1 << (x % 8)))
# define GLOB_SET_CLOSE(str, x) (*(str + x / 8) |= (1 << (x % 8)))

typedef struct	s_brace_exp
{
	char	*begin;
	char	*end;
	t_list	word;
}				t_brace_exp;

typedef struct	s_brace_check
{
	char			*last_beg;
	char			*closed;
	char			already_close;
	t_brace_exp		valide;
}				t_brace_check;

char	brace_valide_type(t_brace_check *brace, char **curs);

#endif
