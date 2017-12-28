/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:00:37 by bviala            #+#    #+#             */
/*   Updated: 2017/12/21 19:27:07 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	builtin_history(void)
{
	size_t	len;
	size_t	len_max;
	t_ldl	*tmp;

	if (!g_sh.history)
		return (-1);
	len = 1;
	len_max = ft_count_len(g_sh.history->length);
	tmp = g_sh.history->head;
	if (!tmp)
		return (0);
	while (tmp)
	{
		DEBUG("AAA");
		ft_putnchar(' ', len_max - ft_count_len(len));
		ft_printf("%zu  %s\n", len, tmp->content);
		tmp = tmp->next;
		++len;
	}
	return (0);
}
