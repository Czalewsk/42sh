/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:00:37 by bviala            #+#    #+#             */
/*   Updated: 2018/03/08 21:58:11 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	display_history(char **argv)
{
	size_t	len;
	size_t	len_max;
	t_ldl	*tmp;

	(void)argv;
	if (!g_sh.history)
		return (-1);
	len = 1;
	len_max = ft_count_len(g_sh.history->length);
	tmp = g_sh.history->head;
	if (!tmp)
		return (0);
	while (tmp)
	{
		ft_putnchar(' ', len_max - ft_count_len(len));
		ft_printf("%zu  %s\n", len, tmp->content);
		tmp = tmp->next;
		++len;
	}
	return (0);
}

int			builtin_history(t_process *p)
{
	char	*options;
	int		ret;

	options = NULL;
	if (!p || !p->argv)
		return (sh_error(-1, 1, NULL, 1, "Fail history builtin\n"));
	if (p->argv[0][0] == '!')
		ret = display_history(p->argv);
	else if (!ft_strcmp(p->argv[0], "history"))
		ret = display_history(p->argv);
	else
		return (sh_error(-1, 1, NULL, 1, "Fail history builtin\n"));
	ft_strdel(&options);
	return (ret);
}
