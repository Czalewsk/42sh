/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:05:19 by bviala            #+#    #+#             */
/*   Updated: 2017/11/15 18:19:38 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldl_head	*ft_ldl_find(t_ldl_head *ldl_head, int (*fcmp)(),
			size_t size, void *content)
{
	t_ldl_head	*ret;
	t_ldl		*temp;

	if (!ldl_head)
		return (NULL);
	temp = ldl_head->head;
	ret = NULL;
	while (temp)
	{
		if (!(fcmp(temp->content, content, size)))
		{
			if (!ret)
				ret = ft_ldl_new_list();
			ret = ft_ldl_addback(ret, temp->content);
		}
		temp = temp->next;
	}
	return (ret);
}
