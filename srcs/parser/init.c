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
	if (((p = (t_process *)malloc(sizeof(t_process)))) == NULL)
		return (NULL);
	p->next = NULL;
	p->argv = NULL;
	p->pid = -1;
	// p->completed = 47;
	// p->stopped = 47;
	p->status = -1;
	return (p);
}

t_job		*init_job(t_job *new)
{
	if ((new = (t_job *)malloc(sizeof(t_job))) == NULL)
		return (NULL);
	new->next = NULL;
	new->command = NULL;
	new->first_process = NULL;
	new->pgid = -1;
//	new->notified = 47;
//	new->tmodes = NULL;
	new->stdin = STDIN_FILENO;
	new->stdout = STDOUT_FILENO;
	new->stderr = STDERR_FILENO;
	return (new);
}

t_tree		*init_node(t_token c, t_tree *n)
{
	if ((n = (t_tree *)malloc(sizeof(t_tree))) == NULL)
		return (NULL);
	n->previous = NULL;
	n->father = NULL;
	n->right = NULL;
	n->left = NULL;
	n->token = c;
	return (n);
}