/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_wordtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 17:06:23 by bviala            #+#    #+#             */
/*   Updated: 2017/09/14 17:23:03 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rev_wordtab(char **tab)
{
	int		size;
	int		i;

	if (!tab || !(*tab))
		return ;
	size = 0;
	while (tab[size])
		size++;
	i = 0;
	while ((size - i) / 2)
	{
		ft_swap((void **)&tab[i], (void **)&tab[size - i - 1]);
		i++;
	}
}
