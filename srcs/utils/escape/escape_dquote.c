/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_escape_dquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 20:54:18 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/21 18:56:40 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_escape.h"

void	*esc_d_bq(char *str, char *to_remove, int index)
{
	(void)str;
	(void)to_remove;
	(void)index;
	return (&sh_esc_dquote);
}

void	*esc_dquote_dq(char *str, char *to_remove, int index)
{
	(void)str;
	set_remove(to_remove, index);
	++g_nb_remove;
	return (&escape_fonctions);
}

void	*esc_dquote_bs(char *str, char *to_remove, int index)
{
	if (!*(str + 1) || !ft_strchr("$`\"\\\n", *(str + 1)))
		return (&sh_esc_dquote);
	set_remove(to_remove, index);
	++g_nb_remove;
	return (&sh_esc_dquote);
}

void				*sh_esc_dquote(char *str, char *to_remove, int index)
{
	const char	not_echapped[] = "$`\\\"";
	void	*(*const fcts[4])(char *, char *, int) =
	{&esc_d_bq, &esc_d_bq, &esc_dquote_bs, &esc_dquote_dq};
	void		*ret;
	long int	esc;

	if (!(esc = (long)ft_strchr(not_echapped, *str)))
		ret = &sh_esc_dquote;
	else
		ret = (void*)fcts[esc - (long int)not_echapped](str,
				to_remove, index);
	return (ret);
}
