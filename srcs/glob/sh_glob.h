/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:54:36 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 08:05:25 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SH_GLOB_H
# define __SH_GLOB_H

# include "ft_sh.h"
# include "libft.h"

# define GLOB_CHECK_CLOSE(str, x) ((int)((*(str + x) == x)))
# define GLOB_SET_CLOSE(str, x) (*str = x)

typedef struct	s_brace_exp
{
	char	*begin;
	char	*end;
	t_list	*word;
	int		nb[2];
	char	seq[2];
	char	mode;
}				t_brace_exp;

typedef struct	s_brace_check
{
	char			*last_beg;
	unsigned char	*closed;
	char			already_close;
	t_brace_exp		valide;
}				t_brace_check;

char	brace_valide_type(t_brace_check *brace, char **curs, char *tkkn);
void	brace_fill_seq_choice(char *str, char *end, t_brace_exp *valide,
		unsigned char *closed);
void	brace_fill_seq_num(char *str, t_brace_exp *valide);

#endif
