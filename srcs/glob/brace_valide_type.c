/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_valide_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:47:53 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 19:56:06 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

//Ajouter Warning si un des nombres est plus grands qu'un int
//ils sera tronque a sa borne la plus proche
char	brace_seq_num(char *curs, char *end, t_brace_exp *valide)
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
	if ((curs + i + j + 2) != end)
		return (0);
	valide->nb[0] = i;
	valide->nb[1] = j;
	valide->mode = 3;
	return (1);
}

char	brace_seq_alpha(char *curs, t_brace_exp *valide)
{
	if (!ft_isalpha(*curs))
		return (0);
	if (*(curs + 1) != '.' || *(curs + 2) != '.')
		return (0);
	if (!ft_isalpha(*(curs + 3)) ||
			ft_islower(*(curs + 3)) != ft_islower(*curs))
		return (0);
	valide->seq[0] = *curs;
	valide->seq[1] = *(curs + 3);
	valide->mode = 2;
	return (1);
}

char	brace_exp_seq(char *curs, char *end, t_brace_exp *valide)
{
	if (curs + 4 >= end)
		return (0);
	if (brace_seq_alpha(curs + 1, valide)
			|| brace_seq_num(curs + 1, end, valide))
		return (1);
	return (0);
}

char	brace_exp_choice(char *curs, char *end, t_brace_check *brace,
		char *tkkn)
{
	static unsigned char	index;
	int						coma;

	index++;
	coma = 0;
	*(brace->closed + (curs - tkkn)) = index;
	while (++curs < end)
	{
		if (*curs == '\\')
			curs += (*(curs + 1) && *(curs + 2)) ? 2 : 1;
		if (*curs == ',' && !*(brace->closed + (curs - tkkn)))
		{
			*(brace->closed + (curs - tkkn)) = index;
			coma++;
		}
		if (*curs == ' ')
			return (0);
	}
	if (!coma)
		return (0);
	brace->valide.mode = 1;
	return (1);
}

char	brace_valide_type(t_brace_check *brace, char **curs, char *tkkn)
{
	int		ret;

	ret = brace_exp_choice(brace->last_beg, *curs, brace, tkkn) +
		brace_exp_seq(brace->last_beg, *curs, &brace->valide);
	if (ret)
	{
		brace->valide.begin = brace->last_beg;
		brace->valide.end = *curs;
		brace->valide.start = brace->last_beg - tkkn;
		if ((brace->last_beg - 1) < tkkn)
			return (126);
		(*curs) = brace->last_beg - 1;
		return (0);
	}
	(*curs) += 1;
	return (1);
}
