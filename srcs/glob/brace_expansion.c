/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:23:30 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 05:12:24 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_glob.h"

char			brace_find_end(t_brace_check *brace, char **curs, char *tkkn)
{
	if (**curs == '\\')
	{
		(*curs) += (*((*curs) + 1)) ? 2 : 1;
		return (1);
	}
	if (**curs == '}' && !GLOB_CHECK_CLOSE(brace->closed, (*curs - tkkn)))
	{
		if (!brace->already_close)
			GLOB_SET_CLOSE(brace->closed, (*curs - tkkn));
		brace->already_close = 1;
		return (2);
	}
	if (!**curs)
	{
		*curs = brace->last_beg - 1;
		return (*curs <= tkkn ? 126 : 0);
	}
	(*curs)++;
	return (1);
}

char			brace_find_beg(t_brace_check *brace, char **curs, char *tkkn)
{
	if (*curs != tkkn && *(*curs - 1) == '\\')
	{
		if (*curs - 2 < tkkn)
			return (126);
		*curs -= 2;
	}
	else if (**curs == '{')
	{
		brace->last_beg = *curs;
		brace->already_close = 0;
		(*curs)++;
		return (1);
	}
	if (*curs == tkkn)
		return (126);
	(*curs)--;
	return (0);
}

t_brace_exp		brace_find_pattern(char *tkkn)
{
	t_brace_check	brace;
	char			*curs;
	char			state;
	char			(*const f[3])() =
	{&brace_find_beg, &brace_find_end, &brace_valide_type};

	ft_bzero(&brace, sizeof(t_brace_check));
	brace.closed = ft_memalloc(ft_strlen(tkkn) / 8 + 1);
	curs = tkkn + ft_strlen(tkkn);
	state = 0;
	while (42)
	{
		state = f[(int)state](&brace, &curs, tkkn);
		if (state > 4)
			break ;
	}
	return (brace.valide);
}

char			**sh_brace_exp(char *tkkn)
{
	t_brace_exp		res;

	/* Remove '\n' at the end of the line */
	char *nl = ft_strrchr(tkkn, '\n');
	if (nl)
		*nl = '\0';
	/* END */
	/* TEST GLOB FIND PATTERN	*/
	if ((res = brace_find_pattern(tkkn)).end)
	{
		ft_printf("\nValide\n");
		ft_printf("Debut=%s|\n", res.begin);
		ft_printf("end  =%s|\n", res.end);
	}
	else
		ft_printf("\nPAS valide\n");
	/* FIN DU TEST				*/
	return (NULL);
}
