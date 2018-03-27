/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 21:15:11 by bviala            #+#    #+#             */
/*   Updated: 2018/03/26 14:15:51 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char	*expoint_contain(char *str)
{
	char	*new;
	t_ldl	*ldl;

	new = NULL;
	ldl = g_sh.history->head;
	while (ldl && !ft_strstr(ldl->content, str))
		ldl = ldl->next;
	if (ldl)
		new = ft_strdup(ldl->content);
	return (new);
}

static char	*expoint_start(char *str)
{
	char	*new;
	size_t	len;
	t_ldl	*ldl;

	new = NULL;
	len = ft_strlen(str);
	ldl = g_sh.history->head;
	while (ldl && ft_strncmp(str, ldl->content, len))
		ldl = ldl->next;
	if (ldl)
		new = ft_strdup(ldl->content);
	return (new);
}

static char	*expoint_isnumber(char *str)
{
	char	*new;
	t_ldl	*ldl;
	int		nb;

	new = NULL;
	if (!(nb = ft_atoi(str)))
		return (NULL);
	if (nb > 0)
	{
		ldl = g_sh.history->tail;
		while (ldl && --nb > 0)
			ldl = ldl->prev;
	}
	else
	{
		ldl = g_sh.history->head;
		while (ldl && ++nb < 0)
			ldl = ldl->next;
	}
	if (ldl)
		new = ft_strdup(ldl->content);
	return (new);
}

static int	check_entry(char *str, char **new)
{
	*new = NULL;
	if (!str || str[0] != '!')
		return (1);
	DEBUG("str is |%s|\n", str);
	if (!str[1] || str[1] == ' ')
	{
		*new = ft_strdup(str);
		return (1);
	}
	if (!g_sh.history || !g_sh.history->head)
		return (1);
	return (0);
}

int			history_expoint(char *str, char **new)
{
	char	*save;

	if (check_entry(str, new))
		return (new ? 0 : -1);
	save = ft_strdup(g_sh.history->head->content);
	ft_ldl_del_id(g_sh.history, 1, &ft_strdel);
	if (str[1] && str[1] == '!' && g_sh.history && g_sh.history->head)
		*new = ft_strdup(g_sh.history->head->content);
	else if (ft_strisnumber(str + 1))
		*new = expoint_isnumber(str + 1);
	else if (str[1] && (str[1] == '?'))
		*new = expoint_contain(str + 2);
	else if (str[1])
		*new = expoint_start(str + 1);
	if (new && *new)
	{
		save = change_expoint_h(save, str, *new);
		update_expoint_h(g_sh.history, save);
		return (1);
	}
	else
		update_expoint_h(g_sh.history, save);
	return (-1);
}
