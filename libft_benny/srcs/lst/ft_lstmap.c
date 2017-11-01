/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:14:36 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 13:14:37 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list	*maillon;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	if (!(maillon = f(lst)))
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp = f(lst)))
			return (NULL);
		ft_lstaddback(&maillon, tmp);
	}
	return (maillon);
}
