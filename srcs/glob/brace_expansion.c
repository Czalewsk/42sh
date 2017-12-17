/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/17 21:56:09 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static void			init_brace_res(t_glob_res *res, char *tkkn)
{
	res->array = ft_memalloc(sizeof(char*) * (BRACE_DEFAULT_SIZE + 1));
	res->size_max = BRACE_DEFAULT_SIZE;
	res->size_actual = 1;
	res->array[0] = ft_strdup(tkkn);
}

char			**sh_brace_exp(char *tkkn)
{
	char			*tmp;
	long			i;
	t_brace_exp		find;
	t_glob_res		res;
	void	(*const f[4])(char *, t_glob_res *, t_brace_exp *, long) =
	{NULL, &brace_expand_choice,
		&brace_expand_deq_alpha, &brace_expand_deq_num};

	i = 0;
	/* Remove '\n' at the end of the line */
	char *nl = ft_strrchr(tkkn, '\n');
	if (nl)
		*nl = '\0';
	/* END */
	init_brace_res(&res, tkkn);
	while (i < res.size_actual)
	{
		tmp = ft_strdup(res.array[i]);
		find = brace_find_pattern(tmp);
		if (find.end)
		{
			f[(int)find.mode](tmp, &res, &find, i);
			i = 0;
			ft_strdel(&tmp);
			continue ;
		}
		ft_strdel(&tmp);
		i++;
	}
	/* TEST GLOB FIND PATTERN	*/
	write(1,"\n",1);
	while (*res.array)
		ft_printf(" %s", *res.array++);
	write(1,"\n",1);
	/* FIN DU TEST*/
	return (NULL);
}
