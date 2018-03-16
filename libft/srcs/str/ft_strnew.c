/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:55:50 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:09:13 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*tab;

	tab = (char*)ft_memalloc(sizeof(char) * size + 1);
	while (size)
	{
		tab[size] = '\0';
		size--;
	}
	tab[size] = '\0';
	return (tab);
}
