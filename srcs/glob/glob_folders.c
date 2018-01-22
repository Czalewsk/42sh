/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:50:04 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/22 07:09:27 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

t_list		*glob_folders_get(char *path, unsigned deep,
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
			folder->deep = deep;
			ft_strdel((char**)&tmp->content);
			tmp->content = folder;
		}
		tmp = next;
	}
	/* TEST */
	/*
	tmp = folders;
//	DEBUG("\nFolders in [%s]:\n", path);
	while (tmp)
	{
		folder = tmp->content;
//		DEBUG("[%s]\n", folder->path);
		tmp = tmp->next;
	}
	*/
	/* END TEST */
	return (folders);
}

char		*glob_is_relative(t_list **path)
{
	char	*ret;
	t_glob_process	*elmt;

	elmt = (*path)->content;
	if (*elmt->path == '/' || (*elmt->path == '.'
				&& *(elmt->path + 1) == '/'))
	{
		ret = ft_strdup(elmt->path);
		ft_lst_remove_index(path, 0, NULL);
	}
	else
		ret = ft_strdup("./");
	return (ret);
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
					glob_folders_get(file->path, deep, elmt->rules));
		if (file->deep != deep)
			ft_lst_remove(folders, tmp, NULL);
		tmp = next;
	}
}

t_list		*glob_folders_init(t_list **path)
{
	t_list		*folders;

	folders = glob_folders_get(glob_is_relative(path), 0,
			((t_glob_process*)((*path)->content))->rules);
	ft_lst_remove_index(path, 0, NULL);
	while ((*path)->next)
	{
		glob_folders_add(&folders, (*path)->content, 1);
		ft_lst_remove_index(path, 0, NULL);
	}
	/* DEBUG */
	/*
	t_list *tmp;
	tmp = folders;
	while (tmp)
	{
		DEBUG("[%s]\n", ((t_glob_files*)tmp->content)->path);
		tmp = tmp->next;
	}
	*/
	/* END DEBUG */
	return (folders);
}

/*
t_list		*glob_folders_init(t_list *path)
{
	t_list			*folders;
	t_list			*next;
	t_list			*tmp;
	unsigned		deep;
	size_t			i;

	if (!path || !path->next)
		return (NULL);
	deep = 1;
	folders = glob_folders_get(glob_is_relative(&path), 0,
			((t_glob_process*)(path->content))->rules);
	i = ft_lstlen(path);
	ft_printf("I=%d|\n", i);
	while (deep < i)
	{
		tmp = folders;
		while (tmp)
		{
			DEBUG("deep=%d | current deep=%d Path to search=%s|\n", deep, ((t_glob_files*)tmp->content)->deep, ((t_glob_files*)tmp->content)->path);
			if (deep - 1 == ((t_glob_files*)tmp->content)->deep)
			{
				DEBUG("path=%s|\n", ((t_glob_files*)tmp->content)->path);
				ft_lstaddback(&folders, glob_folders_get(((t_glob_files*)tmp->content)->path, deep, ((t_glob_process*)path->content)->rules));
				tmp = tmp->next;
			}
			else
			{
				next = tmp->next;
				ft_lst_remove(&folders, tmp, NULL);
				tmp = next;
			}
		}
		path = path->next;
		deep++;
	}
	return (NULL);
}
*/
