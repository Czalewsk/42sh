/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 07:50:07 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 07:52:06 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew_str(char *str, size_t content_size)
{
	t_list	*maillon;

	if (!(maillon = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!str)
	{
		maillon->content = NULL;
		maillon->content_size = 0;
	}
	else
	{
		if (!(maillon->content = ft_memalloc(content_size)))
			return (NULL);
		maillon->content = str;
		maillon->content_size = content_size;
	}
	maillon->next = NULL;
	return (maillon);
}
