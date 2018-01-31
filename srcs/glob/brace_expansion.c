/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/29 16:17:47 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

t_list			*sh_brace_exp(char *tkkn)
{
	t_list			*tmp;
	long			i;
	t_brace_exp		find;
	t_list			*res;
	void			(*const	f[4])(char *, t_list *, t_brace_exp *) =
	{NULL, &brace_expand_choice,
		&brace_expand_deq_alpha, &brace_expand_deq_num};

	i = 0;
	res = NULL;
	ft_lstadd(&res, ft_lstnew_str(ft_strdup(tkkn), 42), 0);
	tmp = res;
	while (tmp)
	{
		find = brace_find_pattern(tmp->content);
		if (find.end)
		{
			f[(int)find.mode](tmp->content, tmp, &find);
			tmp = res;
			continue ;
		}
		tmp = tmp->next;
	}
	return (res);
}
