/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 17:34:15 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

static void			init_brace_res(t_glob_res *res)
{
	res->array = ft_memalloc(sizeof(char*) * (BRACE_DEFAULT_SIZE + 1));
	res->size_max = BRACE_DEFAULT_SIZE;
	res->size_actual = 0;
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
	/* Remove '\n' at the end of the line */
	char *nl = ft_strrchr(tkkn, '\n');
	if (nl)
		*nl = '\0';
	/* END */
	find = brace_find_pattern(tkkn);
	f[(int)find.mode](tkkn ,&res, &find, i);
	/* TEST GLOB FIND PATTERN	*/
	write(1,"\n",1);
	while (*res.array)
		ft_printf(" %s", *res.array++);
	write(1,"\n",1);
	/* FIN DU TEST*/
	return (NULL);
}
