/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:55:19 by bviala            #+#    #+#             */
/*   Updated: 2018/01/30 05:44:32 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMP_H
# define __COMP_H

typedef struct	s_comp
{
	t_ldl_head			*head;
	char				*search;
	int					nb_item;
	int					nb_col_visible;
	int					nb_col;
	int					nb_item_col;
	int					len_max;

}				t_comp;

typedef struct	s_select
{
	char	*name;
	int		color;
	int		is_current;
	size_t	len;
}				t_select;

char	sh_comp(t_buf *cmd, t_read *info, t_key *entry);
char	history_to_completion(t_buf *cmd, t_read *info, t_key *entry);
char	completion_to_normal(t_buf *cmd, t_read *info, t_key *entry);
#endif
