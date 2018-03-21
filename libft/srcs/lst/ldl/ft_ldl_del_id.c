/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_del_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:07:10 by bviala            #+#    #+#             */
/*   Updated: 2018/03/21 10:48:46 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_del_id(t_ldl_head *ldl_head, size_t pos, void (*del)())
{
	t_ldl	*temp;
	t_ldl	*next;
	size_t	i;

	if (!ldl_head || !pos || pos > ldl_head->length)
		return ;
	i = 0;
	temp = ldl_head->head;
	while (temp && i++ <= pos)
	{
		next = temp->next;
		if (i == pos)
			ft_ldl_del(ldl_head, &temp, del);
		temp = next;
	}
}
