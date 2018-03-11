/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 14:50:28 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/11 18:46:25 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		signal_sigint(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	(void)sig;
	g_new_prompt = 1;
	g_sh.exitstatus = 1;
}
