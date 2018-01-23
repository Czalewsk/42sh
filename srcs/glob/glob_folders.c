/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:50:04 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/23 04:25:55 by czalewsk         ###   ########.fr       */
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
			ft_lst_remove(folders, tmp, NULL);
		tmp = next;
	}
}

void		glob_folders_init(t_list **path, unsigned deep_max,
		t_list **folders)
{
	unsigned	deep;

	deep = 1;
	while (deep < deep_max - 1)
	{
		glob_folders_add(folders, (*path)->content, deep++);
		ft_lst_remove_index(path, 0, NULL);
	}
	/*DEBUG*/
	t_list	*tmp;
	tmp = *folders;
	while (tmp)
	{
		DEBUG("folders[%s]\n", ((t_glob_files*)tmp->content)->path);
		tmp = tmp->next;
	}
	/* END */
}
