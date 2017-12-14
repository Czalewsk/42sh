/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 19:56:08 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static void			init_brace_res(t_glob_res *res)
{
	res->array = ft_memalloc(sizeof(char*) * (BRACE_DEFAULT_SIZE + 1));
	res->size_max = BRACE_DEFAULT_SIZE;
	res->size_actual = 1;
}

char			**sh_brace_exp(char *tkkn)
{
	long			i;
	t_brace_exp		find;
	t_glob_res		res;
	void	(*const f[4])(char *, t_glob_res *, t_brace_exp *, long) =
	{NULL, &brace_expand_choice,
		&brace_expand_deq_alpha, &brace_expand_deq_num};

	i = 0;
	init_brace_res(&res);
	ft_bzero(&find, sizeof(t_brace_exp));
	/* Remove '\n' at the end of the line */
	char *nl = ft_strrchr(tkkn, '\n');
	if (nl)
		*nl = '\0';
	/* END */
	res.array[0] = ft_strdup(tkkn);
	while (i < res.size_actual)
	{
		find = brace_find_pattern(res.array[i]);
		if (find.end)
		{
			f[(int)find.mode](tkkn ,&res, &find, i);
			i = 0;
			continue ;
		}
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
