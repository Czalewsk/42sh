/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_is_relative.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 02:42:13 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/24 02:58:41 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

char		glob_is_relative(t_list **path, t_list **folders)
{
	t_glob_process	*elmt;
	t_glob_files	new;

	if (!*path)
		return (0);
	ft_bzero(&new, sizeof(t_glob_files));
	elmt = (*path)->content;
	if (*elmt->path == '/' || (*elmt->path == '.'
				&& *(elmt->path + 1) == '/'))
	{
		new.path = ft_strdup(elmt->path);
		ft_lstadd(folders, ft_lstnew(&new, sizeof(t_glob_files)), 0);
		ft_lst_remove_index(path, 0, &glob_free_process);
		return (0);
	}
	new.path = ft_strdup("./");
	new.is_relative = 1;
	ft_lstadd(folders, ft_lstnew(&new, sizeof(t_glob_files)), 0);
	return (1);
}
