/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 18:06:26 by bviala            #+#    #+#             */
/*   Updated: 2017/09/16 18:06:50 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint_name(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}
