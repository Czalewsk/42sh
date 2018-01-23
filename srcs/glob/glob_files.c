/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 05:32:48 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/23 08:29:26 by czalewsk         ###   ########.fr       */
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
		if (glob_rules_check(tmp->content, rules))
		{
			file = ft_strjoin(path + (is_relative ? 2 : 0), tmp->content);
			ft_strdel((char**)&tmp->content);
			ft_lstinsert_if_end(files,
					ft_lstnew_str(file, ft_strlen(file) + 1), &glob_files_sort);
		}
		ft_lst_remove(&all_files, tmp, free);
		tmp = next;
	}
}

char		glob_is_relative(t_list **path, t_list **folders)
{
	t_glob_process	*elmt;
	t_glob_files	new;

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

t_list		*glob_files(t_list **folders, t_glob_process *path)
{
	t_list			*files;
	t_glob_files	*elmt;
	char			*file;

	files = NULL;
	while (*folders)
	{
		elmt = (*folders)->content;
		if (path->is_root)
		{
			file = ft_strjoin(elmt->path + (elmt->is_relative ? 2 : 0),
					path->path);
			ft_lstinsert_if_end(&files,
					ft_lstnew_str(file, ft_strlen(file) + 1), &glob_files_sort);
		}
		else
			glob_files_add(&files, elmt->path, elmt->is_relative, path->rules);
		ft_lst_remove_index(folders, 0, &glob_free_files);
	}
	return (files);
}

t_list		*glob_files_init(t_list **path)
{
	unsigned	deep_max;
	char		is_relative;
	t_list		*files;
	t_list		*folders;

	folders = NULL;
	is_relative = glob_is_relative(path, &folders);
	deep_max = ft_lstlen(*path);
	if (deep_max > 1)
		glob_folders_init(path, deep_max, &folders);
	files = glob_files(&folders, (*path)->content);
	ft_lstdel(path, &glob_free_process);
	return (files);
}
