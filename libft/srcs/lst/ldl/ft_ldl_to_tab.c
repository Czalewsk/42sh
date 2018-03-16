/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:47:33 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:06:45 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_ldl_to_tab(t_ldl_head *ldl_head)
{
	char		**tab;
	t_ldl		*ldl;
	size_t		size;
	int			index;

	if (!ldl_head)
		return (NULL);
	ldl = ldl_head->head;
	size = ldl_head->length;
	tab = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	index = 0;
	while (ldl)
	{
		tab[index++] = ft_strdup((char *)ldl->content);
		ldl = ldl->next;
	}
	tab[index] = NULL;
	return (tab);
}
