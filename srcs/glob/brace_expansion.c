/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/01 00:34:07 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

char			sh_brace_exp(char *tkkn, t_list **res)
{
	char			exist;
	t_list			*tmp;
	t_brace_exp		find;
	void			(*const	f[4])(char *, t_list *, t_brace_exp *) =
	{NULL, &brace_expand_choice,
		&brace_expand_deq_alpha, &brace_expand_deq_num};

	exist = 0;
	*res = NULL;
	ft_lstadd(res, ft_lstnew_str(ft_strdup(tkkn), 42), 0);
	tmp = *res;
	while (tmp)
	{
		find = brace_find_pattern(tmp->content);
		if (find.end && (exist = 1))
		{
			f[(int)find.mode](tmp->content, tmp, &find);
			tmp = *res;
			continue ;
		}
		tmp = tmp->next;
	}
	if (!exist)
		ft_lstdel(res, &ft_lst_del_str);
	return (exist);
}
