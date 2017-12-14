/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:29:52 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 17:49:33 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

void		glob_buff_handler(long nb_elem, t_glob_res *res)
{
	while (res->size_actual + nb_elem + 1 >= res->size_max)
	{
		res->array = ft_realloc_tab(res->size_max * 4, res->array);
		res->size_max *= 4;
	}
}

void		brace_expand_deq_num(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index)
{
	char	*pre;
	char	*post;
	long	i;
	int		inc;
	char	nb[13];

	ft_bzero(nb, 13);
	inc = find->nb[0] > find->nb[1] ? -1 : 1;
	i = inc < 0 ? find->nb[0] - find->nb[1]
		: find->nb[1] - find->nb[0];
	glob_buff_handler(i, res);
	pre = ft_strsub(tkkn, 0, find->begin - tkkn);
	post = ft_strsub(find->end, 1, ft_strlen(find->end + 1));
	ft_memmove(res->array + index + i, res->array + index,
			sizeof(char**) * (index - res->size_actual));
	res->size_actual += i;
	i = find->nb[0];
	ft_printf("HERE\n");
	while (i != find->nb[1])
	{
		ft_itoa_nm(i, nb);
		res->array[index++] = ft_strxjoin(3, pre, nb, post);
		i += inc;
	}
	ft_itoa_nm(i, nb);
	res->array[index++] = ft_strxjoin(3, pre, nb, post);
}

void		del_str(void *str, size_t size)
{
	(void)size;
	free(str);
}

void		brace_expand_deq_alpha(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index)
{
	char	*pre;
	char	*post;
	long	i;
	int		inc;

	inc = find->seq[0] > find->seq[1] ? -1 : 1;
	i = inc < 0 ? find->seq[0] - find->seq[1]
		: find->seq[1] - find->seq[0];
	glob_buff_handler(i, res);
	pre = ft_strsub(tkkn, 0, find->begin - tkkn);
	post = ft_strdup(find->end);
	ft_memmove(res->array + index + i, res->array + index,
			sizeof(char**) * (index - res->size_actual));
	res->size_actual += i;
	i = find->seq[0];
	while (i != find->seq[1])
	{
		*post = i;
		res->array[index++] = ft_strjoin(pre, post);
		i += inc;
	}
	*post = i;
	res->array[index++] = ft_strjoin(pre, post);
	ft_strdel(&pre);
}

void		brace_expand_choice(char *tkkn, t_glob_res *res,
		t_brace_exp *find, long index)
{
	int		i;
	char	*pre;
	char	*post;
	t_list	*word;

	i = ft_lstlen(find->word);
	glob_buff_handler(i, res);
	pre = ft_strsub(tkkn, 0, find->begin - tkkn);
	post = ft_strsub(find->end, 1, ft_strlen(find->end + 1));
	ft_memmove(res->array + index + i, res->array + index,
			sizeof(char**) * (index - res->size_actual));
	word = find->word;
	i = -1;
	while (word)
	{
		res->array[index + ++i] = ft_strxjoin(3, pre, word->content, post);
		word = word->next;
	}
	res->size_actual += (i + 1);
	ft_strdel(&pre);
	ft_strdel(&post);
	ft_lstdel(&find->word, &del_str);
}
