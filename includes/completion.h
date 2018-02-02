/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:55:19 by bviala            #+#    #+#             */
/*   Updated: 2018/02/01 19:43:48 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMP_H
# define __COMP_H

# define BIN_C 1
# define DIR_C 2
# define WRI_C 4

typedef struct	s_comp
{
	t_ldl_head			*head;
	char				*search;
	int					nb_item;
	int					nb_col;
	int					nb_row;
	int					len_max;
	int					nb_visible;
	int					index;

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
char	sh_comp(t_buf *cmd, t_read *info, t_key *entry);
char	first_comp(t_buf *cmd, t_read *info, t_key *entry, char *to_search);
void	print_comp(t_comp *comp, t_read *info);
void	display_new_comp(t_buf *cmd, t_read *info, t_select *select);
/*
** Change_mode :
** close mode history ou mode auto_completion
*/
char	history_to_completion(t_buf *cmd, t_read *info, t_key *entry);
char	completion_to_normal(t_buf *cmd, t_read *info, t_key *entry);

/*
**	Add_select :
**	liste binaires, $ENV et ls
*/
void	add_ls(t_comp *comp, t_ldl_head *head, char *search);
#endif
