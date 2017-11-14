/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:47:33 by bviala            #+#    #+#             */
/*   Updated: 2017/11/14 15:53:29 by bviala           ###   ########.fr       */
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
	if (!(tab = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	index = 0;
	while (ldl)
	{
		tab[index++] = ft_strdup((char *)ldl->content);
		ldl = ldl->next;
	}
	tab[index] = NULL;
	return (tab);
}
