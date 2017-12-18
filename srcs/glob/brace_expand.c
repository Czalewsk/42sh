/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:29:52 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/18 17:17:20 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

inline static void		brace_update_array(t_glob_res *res, long index, long i)
{
	ft_memmove(res->array + index + i, res->array + index + 1,
			sizeof(char**) * (res->size_actual - index + 1));
	res->size_actual += i;
}

inline static void		brace_pre_expand(char **str[2], char *tkkn,
		t_brace_exp *find)
{
	*(str[0]) = ft_strsub(tkkn, 0, find->start);
	*(str[1]) = ft_strsub(find->end, 1, ft_strlen(find->end + 1));
}

void					brace_expand_deq_num(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index)
{
	char	*pre;
	char	*post;
	long	i;
	int		inc;
	char	nb[13];

	ft_bzero(&nb, 12);
	inc = find->nb[0] > find->nb[1] ? -1 : 1;
	i = inc < 0 ? (find->nb[0] - find->nb[1] + 1)
		: (find->nb[1] - find->nb[0] + 1);
	if (i > 1000000 && ((nb[1] = nb[0] + (inc * 10000000)) || 1))
		i = 1000000;
	glob_buff_handler(i, res);
	brace_update_array(res, index, i);
	brace_pre_expand((char**[2]){&pre, &post}, tkkn, find);
	i = find->nb[0] - inc;
	while ((i = i + inc) != (find->nb[1] + inc))
	{
		ft_itoa_nm(i, nb);
		res->array[index++] = ft_strxjoin(3, pre, nb, post);
	}
	ft_strdel(&pre);
	ft_strdel(&post);
}

void					brace_expand_deq_alpha(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index)
{
	char	alpha[2];
	char	*pre;
	char	*post;
	long	i;
	int		inc;

	inc = find->seq[0] > find->seq[1] ? -1 : 1;
	i = inc < 0 ? (find->seq[0] - find->seq[1] + 1)
		: (find->seq[1] - find->seq[0] + 1);
	glob_buff_handler(i, res);
	brace_update_array(res, index, i);
	brace_pre_expand((char**[2]){&pre, &post}, tkkn, find);
	i = find->seq[0] - inc;
	alpha[1] = '\0';
	while ((i = i + inc) != (find->seq[1] + inc))
	{
		*alpha = i;
		res->array[index++] = ft_strxjoin(3, pre, alpha, post);
	}
	ft_strdel(&pre);
	ft_strdel(&post);
}

void					brace_expand_choice(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index)
{
	int		i;
	char	*pre;
	char	*post;
	t_list	*word;

	i = ft_lstlen(find->word);
	glob_buff_handler(i, res);
	brace_update_array(res, index, i);
	brace_pre_expand((char**[2]){&pre, &post}, tkkn, find);
	word = find->word;
	while (word)
	{
		res->array[index++] = ft_strxjoin(3, pre, word->content, post);
		word = word->next;
	}
	ft_strdel(&pre);
	ft_strdel(&post);
	ft_lstdel(&find->word, &ft_lst_del_str);
}
