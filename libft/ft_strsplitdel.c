/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 16:21:39 by czalewsk          #+#    #+#             */
/*   Updated: 2017/10/18 10:37:01 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strsplitdel(char ***tab)
{
	int		i;
	char	**tmp;

	if (!tab || !(tmp = *tab))
		return ;
	i = -1;
	while (*(tmp + ++i))
		ft_strdel(tmp + i);
	ft_memdel((void**)tab);
}
