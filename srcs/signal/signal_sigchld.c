/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigchld.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 13:19:19 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/16 17:41:35 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		signal_sigchld(void)
{
    // t_job *tmp, *tmp2, *trash;
    // //t_list  *res;
    // update_status();
    // DEBUG("AVANT boucle qui relance les jobs DANS SIGCHLD\n");
	// tmp = g_first_job;
	// while (tmp)
	// {
	// 	if (job_is_running(tmp) == 0 && tmp->foreground == 0 && next_on_tree(tmp->finish_command, tmp->status_last_process) != NULL)
	// 	{
	// 		// if (job_is_completed(tmp))
	// 		// {
	// 		// 	DEBUG("job cmd : %s\n", tmp->command)
	// 		// 	res = pop_job_from_job_order(tmp);
	// 		// 	if (res)
	// 		// 		ft_memdel((void**)&res);
	// 		// 	pop_job_from_first_job(tmp);
	// 		// }
	// 		// else
	// 			DEBUG("job PAS COMPLET\n")
	// 		print_job_order();
	// 		tmp2 = get_new_job(tmp->finish_command, tmp->status_last_process, tmp->foreground);
	// 		//DEBUG("ft_fill_for_jobs : BESOIN DE FREE sur la ligne ref->finish_command = NULL;\n")
	// 		tmp->finish_command = NULL;
	// 		trash = tmp;
	// 		tmp = tmp->next;
	// 		// if (job_is_completed(trash))
	// 		// {
	// 		// 	DEBUG("cmd trash : %s\n", trash->command);
	// 		// 	//del_job(trash);

	// 		// }
	// 		if (!tmp2)
	// 			DEBUG("tmp2  null\n")
	// 		else
	// 			execute_job(tmp2);
	// 	}
	// 	else
    //         tmp = tmp->next;
	// }
    // DEBUG("APRES boucle qui relance les jobs DANS SIGCHLD\n");
}