/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/01/02 17:31:28 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_sh.h"


// t_job *get_new_job(t_job *old)
// {
// 	t_job *new;
// 	if (new = (t_job *)malloc(sizeof(t_job)) == NULL)
// 		return (NULL);
// 	old->next = new;
// 	return (new);
// }

int		ft_fill_for_jobs(t_tree *head)
{
	// t_job	*n;
	t_tree	*tmp;

	// if (first_job = (t_job *)malloc(sizeof(t_job)) == NULL)
	// 	return (-1);
	tmp = head;
	// n = first_job;
	// n->stdin = 0;
	// n->stdout = 1;
	// n->stderr = 2;
	// while (tmp)
	// {
	// 	// if (tmp->token.id == AND || tmp->token.id == AND_IF
	// 	// 	|| tmp->token.id == OR_IF)
	// 	// 	n = get_new_job(n);
	// 	tmp = tmp->right;
	// }
	return (0);
}