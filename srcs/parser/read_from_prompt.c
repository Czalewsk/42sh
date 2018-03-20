/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:06:52 by maastie           #+#    #+#             */
/*   Updated: 2018/01/19 16:06:53 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			read_from_prompt(char **cmd, char *cur)
{
	char	*nfpr;
	int		i;
	int		ret_prompt;

	nfpr = NULL;
	ret_prompt = prompt_add(PROMPT, &nfpr, 0);
	i = cur - (*cmd);
	if (ret_prompt == -3 || ret_prompt == -1)
	{
		ft_strdel(&nfpr);
		return (-1);
	}
	if (nfpr && nfpr[0] != '\n')
		(*cmd) = ft_strjoin_free(*cmd, nfpr, 2);
	else
	{
		ft_strdel(&nfpr);
		return (-8);
	}
	return (read_parser(cmd, (*cmd) + i));
}
