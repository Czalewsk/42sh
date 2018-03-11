/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_background.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:29:53 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/10 14:04:27 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	put_job_in_background(t_job *j, int cont)
{
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			sh_error(1, 0, NULL, 1, "job control: kill SIGCONT");
}
