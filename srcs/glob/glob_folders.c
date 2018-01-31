/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:50:04 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/23 09:29:04 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

t_list		*glob_folders_get(char *path, char is_relative, unsigned deep,
		t_list *rules)
{
	t_list			*folders;
	t_list			*tmp;
	t_glob_files	*folder;
	t_list			*next;

	folders = ft_list_folders(path);
	tmp = folders;
	while (tmp)
	{
		next = tmp->next;
		if (!glob_rules_check(tmp->content, rules))
			ft_lst_remove(&folders, tmp, free);
		else
		{
			folder = ft_memalloc(sizeof(t_glob_files));
			folder->path = ft_strxjoin(3, path, tmp->content, "/");
			folder->is_relative = is_relative;
			folder->deep = deep;
			ft_strdel((char**)&tmp->content);
			tmp->content = folder;
		}
		tmp = next;
	}
	return (folders);
}

void		glob_folders_add(t_list **folders, t_glob_process *elmt,
		unsigned deep)
{
	t_list			*tmp;
	t_glob_files	*file;
	t_list			*next;

	tmp = *folders;
	while (tmp)
	{
		next = tmp->next;
		file = tmp->content;
		if (deep == file->deep + 1)
			ft_lstaddback(folders,
					glob_folders_get(file->path, file->is_relative,
						deep, elmt->rules));
		if (file->deep != deep)
			ft_lst_remove(folders, tmp, &glob_free_files);
		tmp = next;
	}
}

void		glob_add_root(char *root, t_list *folders)
{
	t_glob_files	*tmp;

	while (folders)
	{
		tmp = folders->content;
		tmp->path = ft_strjoin_free(tmp->path, root, 0);
		folders = folders->next;
	}
}

void		glob_folders_init(t_list **path, unsigned deep_max,
		t_list **folders)
{
	unsigned		deep;
	t_glob_process	*tmp;

	deep = 0;
	while (++deep < deep_max)
	{
		tmp = (*path)->content;
		if (tmp->is_root)
			glob_add_root(tmp->path, *folders);
		else
			glob_folders_add(folders, tmp, deep);
		ft_lst_remove_index(path, 0, &glob_free_process);
	}
}
