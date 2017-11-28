/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:14:57 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/28 18:07:25 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_env_cpy(char ***env)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	if (!env || !*env)
		return ;
	while (*(*env + i))
		i++;
	new = ft_memalloc(sizeof(char*) * (++i));
	while (--i >= 0)
		*(new + i) = ft_strdup(*(*env + i));
	*env = new;
}
