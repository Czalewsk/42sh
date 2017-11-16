/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:13:14 by bviala            #+#    #+#             */
/*   Updated: 2017/08/15 18:35:53 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **liste)
{
	t_list	*elem;

	elem = *liste;
	while (elem)
	{
		*liste = elem->next;
		free(elem->content);
		elem->content = NULL;
		free(elem);
		elem = *liste;
	}
	*liste = NULL;
}
