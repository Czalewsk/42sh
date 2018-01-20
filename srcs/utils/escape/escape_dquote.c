/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_escape_dquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 20:54:18 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/06 16:49:31 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_escape.h"

static const void	*esc_d_bq(char *str, char *escaped,
		char *to_remove, int index)
{
	(void)str;
	(void)escaped;
	(void)to_remove;
	(void)index;
	return (&sh_esc_dquote);
}

static const void	*esc_dquote_dq(char *str, char *escaped,
		char *to_remove, int index)
{
	(void)str;
	(void)escaped;
	set_remove(to_remove, index);
	++g_nb_remove;
	set_escape(escaped, index - g_nb_remove, 1);
	return (&escape_fonctions);
}

static const void	*esc_dquote_bs(char *str, char *escaped,
		char *to_remove, int index)
{
	if (!*(str + 1) || !ft_strchr("$`\"\\\n", *(str + 1)))
		return (&sh_esc_dquote);
	set_remove(to_remove, index);
	++g_nb_remove;
	set_escape(escaped, index - g_nb_remove + 1, 0);
	return (&sh_esc_dquote);
}

void				*sh_esc_dquote(char *str, char *escaped, char *to_remove,
		int index)
{
	const char	not_echapped[] = "$`\\\"";
	const void	*(*fcts[4])(char *, char *, char *, int) =
	{&esc_d_bq, &esc_d_bq, &esc_dquote_bs, &esc_dquote_dq};
	void		*ret;
	long int	esc;

	if (!(esc = (long)ft_strchr(not_echapped, *str)))
	{
		ret = &sh_esc_dquote;
		set_escape(escaped, index - g_nb_remove, 0);
	}
	else
		ret = (void*)fcts[esc - (long int)not_echapped](str,
				escaped, to_remove, index);
	return (ret);
}
