/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:36:26 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 13:40:30 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root != 0)
	{
		if (root->left)
			btree_apply_infix(root->left, (*applyf));
		(*applyf)(root->item);
		if (root->right)
			btree_apply_infix(root->right, (*applyf));
	}
}
