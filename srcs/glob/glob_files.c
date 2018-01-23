/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 05:32:48 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/23 04:25:18 by czalewsk         ###   ########.fr       */
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
	tmp = all_files;
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

char		glob_is_relative(t_list **path, t_list **folders)
{
	t_glob_process	*elmt;
	t_glob_files	new;

	elmt = (*path)->content;
	if (*elmt->path == '/' || (*elmt->path == '.'
				&& *(elmt->path + 1) == '/'))
	{
		new.path = ft_strdup(elmt->path);
		ft_lstadd(folders, ft_lstnew(&new, sizeof(t_glob_files)), 0);
		ft_lst_remove_index(path, 0, NULL);
		return (0);
	}
	new.path = ft_strdup("./");
	new.is_relative = 1;
	ft_lstadd(folders, ft_lstnew(&new, sizeof(t_glob_files)), 0);
	return (1);
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

t_list		*glob_files_init(t_list **path)
{
	unsigned	deep_max;
	char		is_relative;
	t_list		*files;
	t_list		*folders;

	folders = NULL;
	deep_max = ft_lstlen(*path);
	is_relative = glob_is_relative(path, &folders);
	if (deep_max > 2)
		glob_folders_init(path, deep_max, &folders);
	files = glob_files(folders, ((t_glob_process*)(*path)->content)->rules);
	return (files);
}
