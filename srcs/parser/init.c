/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:51:09 by maastie           #+#    #+#             */
/*   Updated: 2018/01/11 16:51:10 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_process	*init_process(t_process *p)
{
	p = (t_process *)ft_memalloc(sizeof(t_process));
	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	return (p);
}

t_tree		*init_node(t_token c, t_tree *n)
{
	n = (t_tree *)ft_memalloc(sizeof(t_tree));
	n->token = c;
	return (n);
}
