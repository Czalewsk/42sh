/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/11 20:51:17 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_glob.h"

char	sh_find_beg(char **curs, char **begin, char **end)
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

char	sh_find_end(char **curs, char **begin, char **end)
{
	(void)begin;
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

char	brace_exp_choice(char *curs, char *end)
{
	int		forbidden;

	forbidden = 0;
	while (++curs < end)
	{
		if (*curs == '\\')
			curs += (*(curs + 1) && *(curs + 2)) ? 2 : 1;
		if (*curs == ',')
			forbidden++;
		if (*curs == ' ' || *curs == '{')
			return (0);
	}
		return (forbidden > 0 ? 1 : 0);
}

char	brace_exp_seq(char *curs, char *end)
{
	(void)curs;
	(void)end;
	return (0);
}

char	brace_exp_valide_type(char **curs, char **begin, char **end)
{
	(void)curs;
	/* Retourne 3 ou 4 si VALIDE sinon 1 */
	if (brace_exp_choice(*begin, *end))
		return (3);
	else if (brace_exp_seq(*begin, *end))
		return (4);
	*curs = *end;
	*end = NULL;
	return (1);
}

char	glob_find_pattern(char **curs, char **begin, char **end)
{
	char		*tmp;
	char		state;
	char		(*const f[3])(char **, char **, char **) =
	{&sh_find_beg, &sh_find_end, &brace_exp_valide_type};

	tmp = *curs;
	*begin = NULL;
	state = 0;
	*end = NULL;
	while (42)
	{
		if (*tmp == '\\')
			tmp += (*(tmp + 1) && *(tmp + 2)) ? 2 : 1;
		state = f[(int)state](&tmp, begin, end);
		if (state > 2 || !*tmp)
			break ;
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