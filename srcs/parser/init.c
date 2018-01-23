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
	// if (((p = (t_process *)malloc(sizeof(t_process)))) == NULL)
	// 	return (NULL);
	p = (t_process *)ft_memalloc(sizeof(t_process));
	p->next = NULL;
	p->argv = NULL;
	p->pid = -1;
	p->completed = 48;
	p->stopped = 48;
	p->status = -1;
	p->stdin = dup(STDIN_FILENO);
	p->stdout = dup(STDOUT_FILENO);
	p->stderr = dup(STDERR_FILENO);
	return (p);
}

// t_job		*init_job(t_job *new)
// {
// 	// if ((new = (t_job *)malloc(sizeof(t_job))) == NULL)
// 	// 	return (NULL);
// 	new = (t_job *)ft_memalloc(sizeof(t_job));
// 	// new->next = NULL;
// 	// new->command = NULL;
// 	// new->first_process = NULL;
// 	// new->pgid = -1;
// 	// new->andor = NULL;
// 	// new->notified = 48;
// //	new->tmodes = NULL;
// 	return (new);
// }

// t_run		*init_run(t_run *r)
// {
// 	r = (t_run *)ft_memalloc(sizeof(t_run));
// 	return (r);
// }

t_tree		*init_node(t_token c, t_tree *n)
{
	if ((n = (t_tree *)malloc(sizeof(t_tree))) == NULL)
		return (NULL);
//	n = (t_tree *)ft_memalloc(sizeof(t_tree));
	n->previous = NULL;
	n->father = NULL;
	n->right = NULL;
	n->left = NULL;
	n->token = c;
	return (n);
}