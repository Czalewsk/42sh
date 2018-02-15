/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:33:17 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 14:16:07 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expansions.h"

int		expansions_utils_freelst(t_list *lst, int ret)
{
	t_list	*cur;
	t_list	*prev;

	if (lst)
	{
		cur = lst;
		while (cur)
		{
			free(((t_token*)cur->content)->str);
			free(cur->content);
			prev = cur->next;
			free(cur);
			cur = prev;
		}
	}
	return (ret);
}
