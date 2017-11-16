/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 15:00:05 by bviala            #+#    #+#             */
/*   Updated: 2017/09/14 16:36:22 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		size;
	char	save;

	i = 0;
	size = 0;
	while (str[size] != '\0')
		size++;
	size = size - 1;
	while (i < size)
	{
		save = str[size];
		str[size] = str[i];
		str[i] = save;
		i++;
		size--;
	}
	return (str);
}
