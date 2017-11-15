/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_del_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:28:14 by bviala            #+#    #+#             */
/*   Updated: 2017/11/15 17:59:21 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_del_if(t_ldl_head *ldl_head, int (*fcmp)(),
		void *content, void (*del)())
{
	t_ldl *temp;

	if (!ldl_head || !fcmp)
		return ;
	temp = ldl_head->head;
	while (temp)
	{
		if (!(fcmp(temp->content, content)))
			ft_ldl_del(ldl_head, &temp, del);
		temp = temp->next;
	}
}
