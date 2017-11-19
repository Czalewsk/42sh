/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 11:49:24 by bviala            #+#    #+#             */
/*   Updated: 2017/08/16 14:23:26 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew_c(size_t size, char c)
{
	char	*tab;

	if (!(tab = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	tab[size] = '\0';
	while (size--)
		tab[size] = c;
	return (tab);
}
