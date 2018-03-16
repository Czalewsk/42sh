/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:14:45 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:17:25 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*maillon;

	maillon = (t_list*)ft_memalloc(sizeof(t_list));
	if (!content)
	{
		maillon->content = NULL;
		maillon->content_size = 0;
	}
	else
	{
		maillon->content = ft_memalloc(content_size);
		ft_memcpy(maillon->content, content, content_size);
		maillon->content_size = content_size;
	}
	maillon->next = NULL;
	return (maillon);
}

t_list		*ft_lstnew_str(char *str, size_t content_size)
{
	t_list	*maillon;

	maillon = (t_list*)ft_memalloc(sizeof(t_list));
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
	if (str)
		free(str);
}
