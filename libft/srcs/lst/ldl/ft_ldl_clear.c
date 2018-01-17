/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:56:12 by bviala            #+#    #+#             */
/*   Updated: 2017/12/12 17:37:09 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_clear(t_ldl_head **ldl, void (*del)())
{
	t_ldl *temp;
	t_ldl *to_del;

	if (!ldl || !*ldl)
		return ;
	temp = ft_ldl_head(*ldl);
	while (temp)
	{
		to_del = temp;
		temp = temp->next;
		ft_ldl_del(*ldl, &to_del, del);
	}
	free(*ldl);
	*ldl = NULL;
}
