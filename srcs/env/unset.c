/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 21:05:15 by thugo             #+#    #+#             */
/*   Updated: 2018/03/02 00:03:50 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	env_unsetaddr(t_env **addr)
{
	size_t	len;

	free((*addr)->var);
	free(*addr);
	len = env_len((const t_env **)addr + 1, ENV_LOCAL | ENV_GLOBAL | ENV_TEMP);
	ft_memmove(addr, addr + 1, (len + 1) * sizeof(t_env *));
	g_sh.envupd = 1;
}

void	env_unset(const char *name)
{
	t_env	**found;

	if ((found = env_getaddr(name)))
		env_unsetaddr(found);
}
