/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:02:19 by bviala            #+#    #+#             */
/*   Updated: 2018/02/14 14:35:37 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	fcmp_select_name(t_select *s1, char *name)
{
	if (!s1 || !name)
		return (1);
	return (ft_strcmp(s1->escaped, name));
}

static int	add_env_in_comp(t_comp *comp, t_ldl_head *head, int n, char *name)
{
	t_ldl			*ldl;

	if (!ft_ldl_if_exist(head, &fcmp_select_name, name)
		&& ((!comp->search) ||
		(comp->search && !(ft_strncmp(comp->search, name,
			ft_strlen_utf8(comp->search))))) && ++n)
	{
		ft_ldl_new_node(&ldl, new_select(ft_strdup(name), NULL));
		head = ft_ldl_insert_sort(head, ldl, &fcmp_select);
	}
	ft_strdel(&name);
	return (n);
}

int			add_env(t_comp *comp, t_ldl_head *head, char **env)
{
	int		ret;
	int		len;

	if (!env || !*env)
		return (0);
	ret = 0;
	while (*env)
	{
		len = 0;
		while (((*env) + len) && *((*env) + len) != '=')
			len++;
		ret += add_env_in_comp(comp, head, 0, ft_strndup(*env, len + 1));
		env++;
	}
	return (ret);
}
