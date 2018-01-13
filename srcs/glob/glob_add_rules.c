/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_add_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:47:15 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/13 22:52:56 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

void		glob_add_rules_to_path(t_list *path)
{
	t_glob_process		*elmt;

	while (path)
	{
		elmt = ft_memalloc(sizeof(t_glob_process));
		elmt->path = path->content;
		sh_glob_rules_init(path->content, &elmt->rules);
		path->content = elmt;
		path = path->next;
	}
}
