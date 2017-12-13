/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_valide_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:47:53 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/13 23:48:53 by czalewsk         ###   ########.fr       */
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
		if (*curs == ' ')// || *curs == '{')
			return (0);
	}
	return (coma);
}

char	brace_valide_type(char **curs, char **begin, char **end)
{
	if (brace_exp_choice(*begin, *end))
		return (3);
	else if (brace_exp_seq(*begin, *end))
		return (4);
	*curs = *end;
	*end = NULL;
	return (1);
}
