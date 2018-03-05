/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 21:25:08 by thugo             #+#    #+#             */
/*   Updated: 2018/03/01 21:26:29 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	env_destroy(void)
{
	int		i;

	i = -1;
	while (g_sh.env[++i])
	{
		free(g_sh.env[i]->var);
		free(g_sh.env[i]);
	}
	free(g_sh.env);
}
