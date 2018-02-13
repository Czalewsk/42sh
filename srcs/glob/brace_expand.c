/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:29:52 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/13 11:21:17 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

inline static void		brace_pre_expand(char **str[2], char *tkkn,
		t_brace_exp *find)
{
	*(str[0]) = ft_strsub(tkkn, 0, find->start);
	*(str[1]) = ft_strsub(find->end, 1, ft_strlen(find->end + 1));
}

inline static void		brace_check_value_deq(int inc, long nb[2])
{
	char	n[14];
	char	str[50];

	if ((inc < 0 ? (nb[0] - nb[1] + 1) :
			(nb[1] - nb[0] + 1)) > BRACE_MAX_EXPANSION_NB)
	{
		nb[1] = nb[0] + (inc * BRACE_MAX_EXPANSION_NB);
		ft_itoa_nm(nb[1], n);
		ft_bzero(str, 50);
		ft_strcat(str,
				"Numbers expansion is too large, last number truncated to ");
		ft_strcat(str, n);
		ft_strcat(str, "\n");
		sh_error(str, 0, NULL);
	}
}

void					brace_expand_deq_num(char *tkkn, t_list *tmp,
		t_brace_exp *find)
{
	char	*pre;
	char	*post;
	long	i;
	int		inc;
	char	nb[13];

	ft_bzero(&nb, 12);
	inc = find->nb[0] > find->nb[1] ? -1 : 1;
	brace_check_value_deq(inc, find->nb);
	brace_pre_expand((char**[2]){&pre, &post}, tkkn, find);
	i = find->nb[0];
	ft_itoa_nm(i, nb);
	ft_strdel((char **)&tmp->content);
	tmp->content = ft_strxjoin(3, pre, nb, post);
	while ((i = i + inc) != (find->nb[1] + inc))
	{
		ft_itoa_nm(i, nb);
		ft_lstadd(&tmp->next,
				ft_lstnew_str(ft_strxjoin(3, pre, nb, post), 0), 0);
		tmp = tmp->next;
	}
	ft_strdel(&pre);
	ft_strdel(&post);
}

void					brace_expand_deq_alpha(char *tkkn, t_list *tmp,
		t_brace_exp *find)
{
	char	alpha[2];
	char	*pre;
	char	*post;
	int		inc;

	inc = find->seq[0] > find->seq[1] ? -1 : 1;
	*alpha = inc < 0 ? (find->seq[0] - find->seq[1] + 1)
		: (find->seq[1] - find->seq[0] + 1);
	brace_pre_expand((char**[2]){&pre, &post}, tkkn, find);
	*alpha = find->seq[0];
	alpha[1] = '\0';
	ft_strdel((char **)&tmp->content);
	tmp->content = ft_strxjoin(3, pre, alpha, post);
	while ((*alpha = *alpha + inc) != (find->seq[1] + inc))
	{
		ft_lstadd(&tmp->next,
				ft_lstnew_str(ft_strxjoin(3, pre, alpha, post), 0), 0);
		tmp = tmp->next;
	}
	ft_strdel(&pre);
	ft_strdel(&post);
}

void					brace_expand_choice(char *tkkn, t_list *tmp,
		t_brace_exp *find)
{
	char	*pre;
	char	*post;
	t_list	*word;

	brace_pre_expand((char**[2]){&pre, &post}, tkkn, find);
	ft_strdel((char **)&tmp->content);
	tmp->content = ft_strxjoin(3, pre, find->word->content, post);
	word = find->word->next;
	while (word)
	{
		ft_lstadd(&tmp->next,
				ft_lstnew_str(ft_strxjoin(3, pre, word->content, post), 1), 1);
		tmp = tmp->next;
		word = word->next;
	}
	ft_strdel(&pre);
	ft_strdel(&post);
	ft_lstdel(&find->word, &ft_lst_del_str);
}
