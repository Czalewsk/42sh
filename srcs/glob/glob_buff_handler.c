/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_buff_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:31:33 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/18 16:32:22 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

void		glob_buff_handler(long nb_elem, t_glob_res *res)
{
	while (res->size_actual + nb_elem + 1 >= res->size_max)
	{
		res->array = ft_realloc_tab(res->size_max * 4, res->array);
		res->size_max *= 4;
	}
}
