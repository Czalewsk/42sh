/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:54:36 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/13 08:22:30 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SH_GLOB_H
# define __SH_GLOB_H

# include "ft_sh.h"
# include "libft.h"

# define BRACE_DEFAULT_SIZE (4)

# define BRACE_MAX_EXPANSION_NB (1000)

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

typedef struct	s_glob_rules
{
	char		in[255];
	char		out[255];
	char		single;
	char		directory;
	char		dot;
}				t_glob_rules;

typedef struct	s_glob_process
{
	char		is_root;
	char		is_directory;
	char		*path;
	t_list		*rules;
}				t_glob_process;

typedef struct	s_glob_files
{
	char			*path;
	unsigned int	deep;
	char			is_relative;
}				t_glob_files;

void			glob_buff_handler(long nb_elem, t_glob_res *res);
char			brace_valide_type(t_brace_check *brace, char **curs,
		char *tkkn);
void			brace_fill_seq_choice(char *str, char *end, t_brace_exp *valide,
		unsigned char *closed);
void			brace_fill_seq_num(t_brace_exp *valide);
t_brace_exp		brace_find_pattern(char *tkkn);
void			brace_expand_choice(char *tkkn, t_list *res,
		t_brace_exp *find);
void			brace_expand_deq_num(char *tkkn, t_list *res,
		t_brace_exp *find);
void			brace_expand_deq_alpha(char *tkkn, t_list *res,
		t_brace_exp *find);
char			glob_check_char(unsigned char c);
t_list			*sh_glob_init_path(char *to_glob);
t_glob_rules	glob_rules_square(char **curs, t_list **rules, char add);
t_glob_rules	glob_rules_char(char **curs, t_list **rules, char add);
t_glob_rules	glob_rules_question(char **curs, t_list **rules, char add);
t_glob_rules	glob_rules_asterisk(char **curs, t_list **rules, char add);
char			sh_glob_rules_init(char *str, t_list **rules);
char			glob_add_rules_to_path(t_list *path);
void			glob_folders_init(t_list **path, unsigned deep_max,
		t_list **folders);
char			glob_rules_check(char *str, t_list *rules);
void			sh_glob_add_exp_dot(t_list **rules);
t_list			*glob_files_init(t_list **path);
void			glob_free_files(void *content, size_t size);
void			glob_free_process(void *content, size_t size);
void			glob_free_str(void *elmt, size_t size);
char			glob_is_relative(t_list **path, t_list **folders);
char			sh_brace_exp(char *tkkn, t_list **res);
char			sh_glob(char *to_glob, t_list **files);

#endif
