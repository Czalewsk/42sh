/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:31:53 by maastie           #+#    #+#             */
/*   Updated: 2018/01/11 16:31:54 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"


t_tree	*pipe_process(t_tree *clist, t_job *job)
{
	job->first_process->next = init_process(job->first_process->next);
	job->first_process = job->first_process->next;
	return (clist->right);
}