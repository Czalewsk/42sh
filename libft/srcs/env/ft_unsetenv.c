/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:56:38 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/28 18:07:34 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_unsetenv(char *key, char **env)
{
	char	**to_del;

	if (!key || !env)
		return ;
	if (!(to_del = ft_getenv_addr(env, key)))
		return ;
	while (*env)
		env++;
	ft_strdel(to_del);
	ft_memmove(to_del, to_del + 1, (env - to_del) * sizeof(char**));
}
