/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:50:21 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/28 15:51:47 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_addenv(char *key, char *value, char ***env)
{
	int		i;

	if (!env)
		return ;
	i = 0;
	while (*env && *(*env + i))
		++i;
	*env = ft_realloc_tab(i + 1, *env);
	*(*env + i) = ft_strxjoin(3, key, "=", value);
}
