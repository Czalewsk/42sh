/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/12 13:53:43 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_glob.h"

char	brace_find_beg(char **curs, char **begin, char **end)
{
	if (**curs == '{')
	{
		*end = NULL;
		*begin = *curs;
		(*curs)++;
		return (1);
	}
	return (0);
}

char	brace_find_end(char **curs, char **begin, char **end)
{
	if (**curs == '}')
	{
		*end = *curs;
		return (2);
	}
	if (!**curs)
	{
		*curs = *begin;
		*end = NULL;
		*begin = NULL;
		return (0);
	}
	return (1);
}

char	brace_find_pattern(char *tmp, char **begin, char **end)
{
	char		state;
	char		(*const f[3])(char **, char **, char **) =
	{&brace_find_beg, &brace_find_end, &brace_valide_type};

	*begin = NULL;
	*end = NULL;
	state = 0;
	while (42)
	{
		if (*tmp == '\\')
			tmp += (*(tmp + 1) && *(tmp + 2)) ? 2 : 1;
		state = f[(int)state](&tmp, begin, end);
		if (state > 2 || !*tmp)
			break ;
		tmp++;
	}
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
	if (brace_find_pattern(tkkn, &begin, &end))
		ft_printf("\nValide\n");
	else
		ft_printf("\nPAS valide\n");
	ft_printf("begi=%s|\n", begin);
	ft_printf("end =%s|\n", end);
	/* FIN DU TEST				*/
	return (NULL);
}