/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 05:32:48 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/22 07:37:47 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

int			glob_files_sort(t_list *old, t_list *new)
{
	if (ft_strcmp(old->content, new->content) > 0)
		return (0);
	return (1);
}

void		glob_files_add(t_list **files, char *path, char is_relative,
		t_list *rules)
{
	t_list			*all_files;
	t_list			*tmp;
	char			*file;
	t_list			*next;

	all_files = ft_list_files(path);
	tmp = all_files ;
	while (tmp)
	{
		next = tmp->next;
		DEBUG("file:[%s]->", tmp->content);
		if (glob_rules_check(tmp->content, rules))
		{
			DEBUG("IN\n");
			file = ft_memalloc(sizeof(t_glob_files));
			file = ft_strjoin(path + (is_relative ? 2 : 0), tmp->content);
			ft_strdel((char**)&tmp->content);
			ft_lstinsert_if_end(files,
					ft_lstnew_str(file, ft_strlen(file) + 1), &glob_files_sort);
		}
		else
			DEBUG("OUT\n");
		ft_lst_remove(&all_files, tmp, free);
		tmp = next;
	}
}

t_list		*glob_files(t_list *folders, t_list *rules)
{
	t_list			*files;
	t_list			*next;
	t_glob_files	*elmt;

	files = NULL;
	while (folders)
	{
		next = folders->next;
		elmt = folders->content;
		glob_files_add(&files, elmt->path, elmt->is_relative, rules);
		ft_lst_remove(&folders, folders, NULL);
		folders = next;
	}
	/* DEBUG */
	t_list *tmp;
	tmp = files;
	while (tmp)
	{
		DEBUG("[%s]\n", tmp->content);
		tmp = tmp->next;
	}
	/* END DEBUG */
	return (files);
}



