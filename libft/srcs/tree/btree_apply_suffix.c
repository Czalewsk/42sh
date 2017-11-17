/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:38:14 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 13:42:12 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (root != 0)
	{
		if (root->left)
			btree_apply_suffix(root->left, (*applyf));
		if (root->right)
			btree_apply_suffix(root->right, (*applyf));
		(*applyf)(root->item);
	}
}
