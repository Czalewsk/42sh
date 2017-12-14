/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_valide_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:47:53 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 05:12:44 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_glob.h"

char	brace_seq_num(char *curs, char *end)
{
	int		i;
	int		j;

	if ((i = ft_find_end_nbr(curs)) <= 0)
		return (0);
	if (!*(curs + i) || !*(curs + i + 1) ||
			*(curs + i) != '.' || *(curs + i) != '.')
		return (0);
	if ((j = ft_find_end_nbr(curs + i + 2)) <= 0)
		return (0);
	return ((curs + i + j + 2) != end ? 0 : 1);
}

char	brace_seq_alpha(char *curs)
{
	if (!ft_isalpha(*curs))
		return (0);
	if (*(curs + 1) != '.' || *(curs + 2) != '.')
		return (0);
	if (!ft_isalpha(*(curs + 3)))
		return (0);
	return (1);
}

char	brace_exp_seq(char *curs, char *end)
{
	if (curs + 4 >= end)
		return (0);
	if (brace_seq_alpha(curs + 1) || brace_seq_num(curs + 1, end))
		return (1);
	return (0);
}

char	brace_exp_choice(char *curs, char *end)
{
	int		coma;

	coma = 0;
	while (++curs < end)
	{
		if (*curs == '\\')
			curs += (*(curs + 1) && *(curs + 2)) ? 2 : 1;
		if (*curs == ',')
			coma++;
		if (*curs == ' ')
			return (0);
	}
	return (coma ? 1 : 0);
}

char	brace_valide_type(t_brace_check *brace, char **curs)
{
	int		ret;

	ret = brace_exp_choice(brace->last_beg, *curs) +
		brace_exp_seq(brace->last_beg, *curs);
	if (ret)
	{
		brace->valide.begin = brace->last_beg;
		brace->valide.end = *curs;
	}
	(*curs) += 1;
	return (1);
}
