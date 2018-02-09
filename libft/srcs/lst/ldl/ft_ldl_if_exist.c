/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_if_exist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:12:43 by bviala            #+#    #+#             */
/*   Updated: 2018/02/09 16:41:44 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ldl_if_exist(t_ldl_head *ldl_head, int (*fcmp)(),
		void *content)
{
	t_ldl *temp;

	if (!ldl_head || !fcmp)
		return (-1);
	temp = ldl_head->head;
	while (temp)
	{
		if (!(fcmp(temp->content, content)))
			return (1);
		temp = temp->next;
	}
	return (0);
}
