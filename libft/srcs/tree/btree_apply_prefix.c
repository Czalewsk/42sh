/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:40:48 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 13:41:49 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	if (root != 0)
	{
		(*applyf)(root->item);
		if (root->left)
			btree_apply_prefix(root->left, (*applyf));
		if (root->right)
			btree_apply_prefix(root->right, (*applyf));
	}
}
