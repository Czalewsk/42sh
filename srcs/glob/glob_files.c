/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 05:32:48 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/22 07:14:30 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

int			glob_files_sort(t_list *old, t_list *new)
{
	if (ft_strcmp(((t_glob_files*)old->content)->path,
				((t_glob_files*)new->content)->path) > 0)
		return (1);
	return (0);
}

void		glob_files_add(t_list **files, char *path, t_list *rules)
{
	t_list			*all_files;
	t_list			*tmp;
	t_glob_files	*file;
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
			file->path = ft_strjoin(path, tmp->content);
			ft_strdel((char**)&tmp->content);
			ft_lstinsert_if_end(files,
					ft_lstnew(file, sizeof(t_glob_files*)), &glob_files_sort);
		}
		else
			DEBUG("OUT\n");
		ft_lst_remove(&all_files, tmp, free);
		tmp = next;
	}
}

t_list		*glob_files(t_list *folders, t_glob_process *path)
{
	t_list	*files;
	t_list	*next;

	files = NULL;
	while (folders)
	{
		next = folders->next;
		glob_files_add(&files,
				((t_glob_process*)folders->content)->path, path->rules);
		ft_lst_remove(&folders, folders, NULL);
		folders = next;
	}
	/* DEBUG */
	t_list *tmp;
	tmp = files;
	while (tmp)
	{
		DEBUG("[%s]\n", ((t_glob_files*)tmp->content)->path);
		tmp = tmp->next;
	}
	/* END DEBUG */
	return (files);
}



