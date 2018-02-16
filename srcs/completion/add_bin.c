/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:59:01 by bviala            #+#    #+#             */
/*   Updated: 2018/02/16 15:06:59 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	fcmp_select_name(t_select *s1, char *name)
{
	if (!s1 || !name)
		return (1);
	return (ft_strcmp(s1->escaped, name));
}

static int	add_bin_from_dir(t_comp *comp, t_ldl_head *head, int n, char *path)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	t_ldl			*ldl;
	char			*full_path;

	if (!(dir_stream = opendir(path)))
		return (sh_error(0, 1, NULL, 1, "Fail opendir\n"));
	while ((dir = readdir(dir_stream)) != NULL)
	{
		full_path = ft_strjoin(path, dir->d_name);
		if ((dir->d_name[0] != '.') && ft_is_a_bin(full_path) &&
			!ft_ldl_if_exist(head, &fcmp_select_name, dir->d_name)
			&& ((!comp->search) ||
			(comp->search && !(ft_strncmp(comp->search, dir->d_name,
				ft_strlen_utf8(comp->search))))) && ++n)
		{
			ft_ldl_new_node(&ldl, new_select(ft_strdup(dir->d_name), path));
			head = ft_ldl_insert_sort(head, ldl, &fcmp_select);
		}
		ft_strdel(&full_path);
	}
	closedir(dir_stream);
	return (n);
}

int			add_bin(t_comp *comp, t_ldl_head *head)
{
	int		ret;
	char	**tab_path;
	int		i;

	ret = 0;
	if (!(tab_path = ft_strsplit(ft_getenv(g_sh.env, "PATH"), ':')))
		return (0);
	i = 0;
	while (tab_path && tab_path[i])
	{
		tab_path[i] = ft_strjoin_free(tab_path[i], "/", 0);
		ret += add_bin_from_dir(comp, head, 0, tab_path[i]);
		i++;
	}
	free_tab2d(&tab_path);
	return (ret);
}
