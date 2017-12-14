/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:54:36 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 19:36:24 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SH_GLOB_H
# define __SH_GLOB_H

# include "ft_sh.h"
# include "libft.h"

# define BRACE_DEFAULT_SIZE (4)

# define GLOB_CHECK_CLOSE(str, x) ((int)((*(str + x) == x)))
# define GLOB_SET_CLOSE(str, x) (*str = x)

typedef struct	s_brace_exp
{
	char	*begin;
	int		start;
	char	*end;
	t_list	*word;
	long	nb[2];
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

typedef struct	s_glob_res
{
	char		**array;
	long		size_max;
	long		size_actual;
}				t_glob_res;

char			brace_valide_type(t_brace_check *brace, char **curs,
		char *tkkn);
void			brace_fill_seq_choice(char *str, char *end, t_brace_exp *valide,
		unsigned char *closed);
void			brace_fill_seq_num(t_brace_exp *valide);
t_brace_exp		brace_find_pattern(char *tkkn);
void			brace_expand_choice(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index);
void			brace_expand_deq_num(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index);
void			brace_expand_deq_alpha(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index);

#endif
