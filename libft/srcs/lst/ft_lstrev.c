/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:15:35 by bviala            #+#    #+#             */
/*   Updated: 2017/09/14 16:33:23 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrev(t_list **liste)
{
	t_list	*actual;
	t_list	*suivant;

	suivant = *liste;
	if (*liste)
	{
		suivant = suivant->next;
		(*liste)->next = NULL;
		while (suivant)
		{
			actual = suivant;
			suivant = suivant->next;
			actual->next = *liste;
			*liste = actual;
		}
	}
}
