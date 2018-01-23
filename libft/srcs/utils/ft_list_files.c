/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 14:27:42 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/23 06:55:08 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline int	ft_is_not_root(char *name)
{
	int		len;

	if (!name)
		return (0);
	len = ft_strlen(name);
	if (len > 2)
		return (1);
	else if (len == 1 && *name == '.')
		return (0);
	else if (len == 2 && *name == '.' && *(name + 1) == '.')
		return (0);
	else
		return (1);
}

t_list		*ft_list_files(char *path)
{
	t_list			*ret;
	DIR				*dir;
	struct dirent	*dirent;

	ret = NULL;
	if (!path || !(dir = opendir(path)))
		return (NULL);
	while ((dirent = readdir(dir)))
		if (ft_is_not_root(dirent->d_name))
			ft_lstadd(&ret,
				ft_lstnew(dirent->d_name, ft_strlen(dirent->d_name) + 1), 0);
	closedir(dir);
	return (ret);
}

t_list		*ft_list_folders(char *path)
{
	char			*tmp;
	t_list			*ret;
	DIR				*dir;
	struct dirent	*dirent;
	struct stat		stat_data;

	ret = NULL;
	if (!path || !(dir = opendir(path)) || (stat(path, &stat_data)))
		return (NULL);
	if (!S_ISDIR(stat_data.st_mode) || !(stat_data.st_mode & (S_IXUSR
					| S_IXGRP | S_IXOTH)))
		return (NULL);
	while ((dirent = readdir(dir)))
	{
		if (!ft_is_not_root(dirent->d_name))
			continue ;
		tmp = ft_strjoin(path, dirent->d_name);
		if (!stat(tmp, &stat_data) && (stat_data.st_mode & S_IFMT) == S_IFDIR)
			ft_lstadd(&ret,
				ft_lstnew(dirent->d_name, ft_strlen(dirent->d_name) + 1), 0);
		ft_strdel(&tmp);
	}
	closedir(dir);
	return (ret);
}
/*
**int		main(int ac, char **av)
**{
**	t_list		*files;
**	t_list		*tmp;
**
**	if (ac != 2)
**		return (1);
**	files = ft_list_files(av[1]);
**	while (files)
**	{
**		ft_printf("%s|\n", files->content);
**		tmp = files;
**		files = files->next;
**		ft_strdel((char **)&tmp->content);
**		ft_memdel((void **)&tmp);
**	}
**	return (0);
**}
*/
