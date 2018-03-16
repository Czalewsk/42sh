/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 19:36:37 by bviala            #+#    #+#             */
/*   Updated: 2016/08/24 19:42:36 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*btree_create_node(void *item)
{
	t_btree *new;

	new = ft_memalloc(sizeof(t_btree));
	new->left = 0;
	new->right = 0;
	new->item = item;
	return (new);
}
