/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:56:03 by bviala            #+#    #+#             */
/*   Updated: 2017/12/28 17:26:23 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	history_search_nb(t_buf *cmd, t_read *info, int nb)
{
	t_ldl *tmp;

	if (!nb || !g_sh.history || (nb > (int)g_sh.history->length))
		return ;
	tmp = g_sh.history->tail;
	while (tmp && --nb)
		tmp = tmp->prev;
	if (tmp)
		display_str(cmd, info, tmp->content, ft_strlen(tmp->content));
}

void	history_search_nb_neg(t_buf *cmd, t_read *info, int nb)
{
	t_ldl *tmp;

	if (!nb || !g_sh.history || (nb < (int)g_sh.history->length * (-1)))
		return ;
	tmp = g_sh.history->head;
	while (tmp && ++nb)
		tmp = tmp->next;
	if (tmp)
		display_str(cmd, info, tmp->content, ft_strlen(tmp->content));
}

void	history_search_contain_name(t_buf *cmd, t_read *info, char *str)
{
	t_ldl *tmp;

	if (!str || !g_sh.history)
		return ;
	tmp = g_sh.history->head;
	while (tmp && !ft_strstr(tmp->content, str))
		tmp = tmp->next;
	if (tmp)
		display_str(cmd, info, tmp->content, ft_strlen(tmp->content));
}

void	history_search_begin_name(t_buf *cmd, t_read *info, char *str)
{
	t_ldl *tmp;

	if (!str || !g_sh.history)
		return ;
	tmp = g_sh.history->head;
	while (tmp && ft_strncmp(str, tmp->content, ft_strlen(str)))
		tmp = tmp->next;
	if (tmp)
		display_str(cmd, info, tmp->content, ft_strlen(tmp->content));
}
