/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:13:27 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 13:13:30 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstcmp(t_list **lst, char *str)
{
	t_list	*temp;

	temp = *lst;
	while (lst)
	{
		if ((ft_strcmp(str, temp->content)) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}
