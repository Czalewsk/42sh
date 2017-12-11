/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/11 18:13:42 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_glob.h"

void		sh_find_beg(char **curs, char **begin, char **end, int *state)
{
	if (**curs == '{')
	{
		*end = NULL;
		*begin = *curs;
		(*curs)++;
		*state = 1;
	}
}

int		sh_find_end(char **curs, char **begin, char **end)
{
	(void)begin;
	if (**curs == '}')
	{
		*end = *curs;
		return (2);
	}
	return (1);
}

int		brace_exp_valide_type(char **curs, char **begin, char **end)
{
	/* Retourne 2 ou 3 si VALIDE sinon 1 */
	if (brace_exp_choice(curs, begin, end))
		return (2);
	else if (brace_exp_seq(curs, begin, end))
		return (3);
	return (1);
}

char	glob_find_pattern(char **curs, char **begin, char **end)
{
	char		*tmp;
	int			state;

	tmp = *curs;
	*begin = NULL;
	state = 0;
	*end = NULL;
	while (*tmp && state < 2)
	{
		if (*tmp == '\\')
			tmp += (*(tmp + 1) && *(tmp + 2)) ? 2 : 1;
		sh_find_beg(&tmp, begin, end, &state);
		if (state)
			sh_find_end(&tmp, begin, end);
		if (*end)
			state = brace_exp_valide_type(&tmp, begin, end);
		tmp++;
	}
	*curs = tmp;
	return (*end ? state : 0);
}

char	**sh_brace_exp(char *tkkn)
{
	t_brace_exp		brace;

	/* Remove '\n' at the end of the line */
	char *nl = ft_strrchr(tkkn, '\n');
	if (nl)
		*nl = '\0';
	/* END */
	ft_bzero(&brace, sizeof(t_brace_exp));
	/* TEST GLOB FIND PATTERN	*/
	char *begin = NULL;
	char *end = NULL;
	char *curs;
	curs = tkkn;
	if (glob_find_pattern(&curs, &begin, &end))
		ft_printf("\nValide\n");
	else
		ft_printf("\nPAS valide\n");
	ft_printf("curs=%s|\n", curs);
	ft_printf("begi=%s|\n", begin);
	ft_printf("end =%s|\n", end);
	/* FIN DU TEST				*/
	return (NULL);
}