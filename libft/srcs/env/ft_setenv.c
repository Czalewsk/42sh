/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:33:54 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/28 18:07:51 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_setenv(char *key, char *value, char ***env)
{
	long		i;

	(void)value;
	if (!env || !*env)
		return ;
	if ((i = ft_getenv_addr(*env, key) - *env) < 0)
		ft_addenv(key, value, env);
	else
	{
		ft_strdel(*env + i);
		*(*env + i) = ft_strxjoin(3, key, "=", value);
	}
}
