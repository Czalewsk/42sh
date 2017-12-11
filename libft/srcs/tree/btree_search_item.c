/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:45:06 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 13:47:03 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*btree_search_item(t_btree *root, void *data_ref,
		int (*cmpf)(void *, void *))
{
	if (root == 0)
		return (root);
	else
	{
		if (cmpf(data_ref, root->item) < 0)
			return (btree_search_item(root->left, data_ref, cmpf));
		if (cmpf(data_ref, root->item) == 0)
		{
			return (root->item);
		}
		if (cmpf(data_ref, root->item) >= 0)
			return (btree_search_item(root->right, data_ref, cmpf));
	}
	return (0);
}
