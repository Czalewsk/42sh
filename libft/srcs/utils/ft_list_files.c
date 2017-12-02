/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 14:27:42 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/02 18:01:49 by czalewsk         ###   ########.fr       */
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
	if (!path)
		return (NULL);
	if (!(dir = opendir(path)))
		return (NULL);
	while ((dirent = readdir(dir)))
		ft_lstadd(&ret,
				ft_lstnew(dirent->d_name, ft_strlen(dirent->d_name) + 1), 0);
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