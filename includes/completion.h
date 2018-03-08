/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:55:19 by bviala            #+#    #+#             */
/*   Updated: 2018/03/08 18:28:35 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMPLETION_H
# define __COMPLETION_H

# define BIN_C 1
# define DIR_C 2
# define WRI_C 4

typedef struct	s_comp
{
	t_ldl_head			*head;
	char				*search;
	char				*path;
	int					win_height;
	int					nb_file;
	int					nb_file_col;
	int					nb_col;
	int					nb_col_visible;
	int					len_max;
	int					index_col;
	int					first;
	int					part;
	int					ret;
}				t_comp;

typedef struct	s_select
{
	char	*name;
	char	*escaped;
	int		color;
	int		is_current;
	size_t	len;
}				t_select;

/*
**	sh_comp + print_comp :
**	Algo et display de l'autocompletion
*/
void			calcul_display(t_comp *comp, t_read *info, t_buf *cmd);
t_ldl			*get_current(t_ldl_head *lst);
char			sh_comp(t_buf *cmd, t_read *info, t_key *entry);
char			first_comp(t_buf *cmd, t_read *info,
					t_key *entry, char *to_search);
void			print_comp(t_comp *comp, t_read *info, t_buf *cmd);
void			display_new_comp(t_buf *cmd,
					t_read *info, t_select *select);
void			clear_prompt_comp(t_comp *comp);
void			comp_signal(t_buf *cmd, t_read *info);
/*
** arrow_comp :
** Se deplacer visuellement en auto_completion;
*/
char			comp_arrow_down(t_buf *cmd, t_read *info, t_key *entry);
char			comp_arrow_up(t_buf *cmd, t_read *info, t_key *entry);
char			comp_arrow_left(t_buf *cmd, t_read *info, t_key *entry);
char			comp_arrow_right(t_buf *cmd, t_read *info, t_key *entry);

/*
** Change_mode :
** close mode auto_completion
*/
char			completion_to_normal(t_buf *cmd, t_read *info, t_key *entry);
char			validate_completion(t_buf *cmd, t_read *info, t_key *entry);
char			quit_completion(t_buf *cmd, t_read *info, t_key *entry);
char			completion_to_normal_char(t_buf *cmd, t_read *info,
				t_key *entry);

/*
**	Add_select :
**	liste binaires, $ENV et ls
*/
int				fcmp_select(t_select *s1, t_select *s2);
t_select		*new_select(char *name, char *path);
void			add_ls(t_comp *comp, t_ldl_head *head, char *search);
int				add_dir(t_comp *comp, t_ldl_head *head);
int				add_bin(t_comp *comp, t_ldl_head *head);
int				add_env(t_comp *comp, t_ldl_head *head, char **env);
#endif
