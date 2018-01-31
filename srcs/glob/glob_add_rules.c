/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_add_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:47:15 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/24 02:37:33 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

char		glob_rules_check_root(char *str)
{
	if (*str == '.')
		str++;
	else
		return (0);
	if (*str == '/' || !*str)
		return (1);
	if (*str == '.')
		return (glob_rules_check_root(str));
	return (0);
}

char		glob_rules_directory(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

void		glob_add_rules_to_path(t_list *path)
{
	t_glob_process		*elmt;

	while (path)
	{
		elmt = ft_memalloc(sizeof(t_glob_process));
		elmt->path = path->content;
		if (glob_rules_directory(path->content))
			elmt->is_directory = 1;
		if (glob_rules_check_root(path->content))
			elmt->is_root = 1;
		else
			sh_glob_rules_init(path->content, &elmt->rules);
		path->content = elmt;
		path = path->next;
	}
}
