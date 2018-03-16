/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 11:49:24 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:09:20 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew_c(size_t size, char c)
{
	char	*tab;

	tab = (char*)ft_memalloc(sizeof(char) * size + 1);
	tab[size] = '\0';
	while (size--)
		tab[size] = c;
	return (tab);
}
