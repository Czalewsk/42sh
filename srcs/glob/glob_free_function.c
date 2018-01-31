/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_free_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 07:01:48 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/23 08:14:14 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

void		glob_free_rules(void *content, size_t size)
{
	(void)size;
	free(content);
}

void		glob_free_process(void *content, size_t size)
{
	t_glob_process	*elmt;

	(void)size;
	elmt = content;
	ft_lstdel(&elmt->rules, &glob_free_rules);
	ft_strdel(&elmt->path);
	free(content);
}

void		glob_free_files(void *content, size_t size)
{
	t_glob_files	*elmt;

	(void)size;
	elmt = content;
	free(elmt->path);
	free(elmt);
}
