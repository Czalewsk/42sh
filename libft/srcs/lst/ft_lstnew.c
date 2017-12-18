/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:14:45 by bviala            #+#    #+#             */
/*   Updated: 2017/12/18 17:49:15 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*maillon;

	if (!(maillon = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		maillon->content = NULL;
		maillon->content_size = 0;
	}
	else
	{
		if (!(maillon->content = ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(maillon->content, content, content_size);
		maillon->content_size = content_size;
	}
	maillon->next = NULL;
	return (maillon);
}

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
		maillon->content = str;
		maillon->content_size = content_size;
	}
	maillon->next = NULL;
	return (maillon);
}

void		ft_lst_del_str(void *str, size_t size)
{
	(void)size;
	free(str);
}
