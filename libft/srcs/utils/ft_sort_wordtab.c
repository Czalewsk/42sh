/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_wordtab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 19:17:39 by bviala            #+#    #+#             */
/*   Updated: 2017/08/22 11:44:24 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_wordtab(char **tab)
{
	int	i;
	int	sort;

	if (!tab || !(*tab))
		return ;
	sort = 0;
	while (!sort)
	{
		sort = 1;
		i = 0;
		while (tab[i + 1])
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				ft_swap((void **)&tab[i], (void **)&tab[i + 1]);
				sort = 0;
			}
			i++;
		}
	}
}
