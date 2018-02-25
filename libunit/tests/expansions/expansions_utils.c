/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:33:17 by thugo             #+#    #+#             */
/*   Updated: 2018/02/19 03:30:53 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expansions.h"
#include "expansions_utils.h"
#include "libunit_utils.h"

int		expansions_utils_free(char ***venv, t_list **lst, int ret)
{
	t_list	*cur;
	t_list	*prev;

	if (venv && *venv)
	{
		utils_venvdestroy(*venv);
		*venv = NULL;
	}
	if (lst && *lst)
	{
		cur = *lst;
		while (cur)
		{
			free(((t_token*)cur->content)->str);
			free(cur->content);
			prev = cur->next;
			free(cur);
			cur = prev;
		}
		*lst = NULL;
	}
	return (ret);
}
