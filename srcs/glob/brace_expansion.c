/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/11 17:25:10 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_glob.h"

int		sh_find_beg(char **curs, char **begin, char **end)
{
	(void)end;
	if (**curs == '{')
	{
		*begin = *curs;
		return (1);
	}
	if (!**curs)
		return (-1);
	return (0);
}

int		sh_find_end(char **curs, char **begin, char **end)
{
	if (**curs == '}')
	{
		*end = *curs;
		return (2);
	}
	if (!**curs)
	{
		*curs = *begin;
		return (0);
	}
	return (1);
}

int		brace_exp_valide_type(char **curs, char **begin, char **end)
{
	/* Retourne 2 si pas de fin et met curs a begin */
	char	*tmp;

	if (brace_exp_choice(curs, begin, end))
	{
		return (4);
	}
	else if (brace_exp_seq(curs, begin, end))
	{
		return (5);
	}
	else if (!**curs)
	{
		return (1);
	}
	return (2);
}

char	glob_find_pattern(char **curs, char **begin, char **end)
{
	char		*tmp;
	int			state;
	int			(*const f[3])(char **, char **, char **) =
	{&sh_find_beg, &sh_find_end, brace_exp_valide_type};

	tmp = *curs;
	state = 0;
	while (42)
	{
		if (*tmp == '\\')
			tmp += (*(tmp + 1) && *(tmp + 2)) ? 2 : 1;
		state = (f[state](&tmp, begin, end));
		tmp++;
		if (state >= 3 || state < 0)
			break ;
	}
	if (state < 3)
		return (0);
	*curs = tmp;
	return (state - 3);
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