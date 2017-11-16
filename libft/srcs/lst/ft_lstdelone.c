/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:13:59 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 13:14:01 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del) (void*, size_t))
{
	t_list	*elem;

	elem = *alst;
	if (!elem)
		return ;
	else
	{
		del(elem->content, elem->content_size);
		free(elem);
	}
	*alst = NULL;
}
