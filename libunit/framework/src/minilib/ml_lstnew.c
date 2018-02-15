/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 00:20:29 by thugo             #+#    #+#             */
/*   Updated: 2017/03/30 03:04:23 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libunit_types.h"

t_ml_list	*ml_lstnew(void const *content, size_t size)
{
	t_ml_list	*new;

	if (!(new = (t_ml_list *)malloc(sizeof(t_ml_list))))
		return (NULL);
	if (!content)
		new->content = NULL;
	else
	{
		if (!(new->content = malloc(size)))
		{
			free(new);
			return (NULL);
		}
		memcpy(new->content, content, size);
	}
	new->next = NULL;
	return (new);
}
