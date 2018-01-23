/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:13:43 by bviala            #+#    #+#             */
/*   Updated: 2018/01/23 07:03:17 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void *, size_t))
{
	t_list	*elem;
	t_list	*next;

	elem = *alst;
	while (elem)
	{
		next = elem->next;
		if (del)
			del(elem->content, elem->content_size);
		free(elem);
		elem = next;
	}
	*alst = NULL;
}
