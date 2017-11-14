/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:27:25 by bviala            #+#    #+#             */
/*   Updated: 2017/11/14 19:00:26 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_remove_if(t_ldl_head *ldl_head, int (*fcmp)(),
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
