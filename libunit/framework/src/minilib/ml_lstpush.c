/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 00:33:33 by thugo             #+#    #+#             */
/*   Updated: 2017/03/30 03:50:48 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libunit_types.h"

void	ml_lstpush(t_ml_list **alst, t_ml_list *new)
{
	t_ml_list	*cur;

	if (!alst || !new)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		cur = *alst;
		while (cur)
		{
			if (!cur->next)
			{
				cur->next = new;
				return ;
			}
			cur = cur->next;
		}
	}
}
