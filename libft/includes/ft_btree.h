/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 19:31:16 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 13:59:47 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_BTREE_H
# define __FT_BTREE_H
# include "libft.h"

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

void				btree_apply_infix(t_btree *root, void (*applyf)(void *));
void				btree_apply_insert_data(t_btree **root, void *item,
					int (*cmpf)(void *, void *));
void				btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void				btree_apply_suffix(t_btree *root, void (*applyf)(void *));
t_btree				*btree_create_node(void *item);
int					btree_level_count(t_btree *root);
void				*btree_search_item(t_btree *root, void *data_ref,
					int (*cmpf)(void *, void *));
#endif
