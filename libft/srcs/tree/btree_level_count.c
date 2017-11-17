/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:44:09 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 13:59:01 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		btree_level_count(t_btree *root)
{
	if (root == 0)
		return (0);
	if (btree_level_count(root->left) > btree_level_count(root->right))
		return (1 + (btree_level_count(root->left)));
	else
		return (1 + (btree_level_count(root->right)));
}
