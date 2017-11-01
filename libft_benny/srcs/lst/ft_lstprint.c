/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:15:24 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 13:15:26 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		ft_putstr("room [");
		ft_putnbr(tmp->content_size);
		ft_putstr("] == ");
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}
