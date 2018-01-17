/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:42:56 by bviala            #+#    #+#             */
/*   Updated: 2017/12/14 17:38:57 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_tab(size_t size, char **tab)
{
	char	**new_tab;
	size_t	i;

	if (!(new_tab = (char **)ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (tab && tab[i] && i < size)
	{
		new_tab[i] = ft_strdup(tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
	new_tab[i] = NULL;
	return (new_tab);
}
