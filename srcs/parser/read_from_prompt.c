/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:06:52 by maastie           #+#    #+#             */
/*   Updated: 2018/03/22 15:50:07 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			read_from_prompt(char **cmd, char **cur)
{
	char	*nfpr;
	int		i;
	int		ret_prompt;
	int		len;

	nfpr = NULL;
	ret_prompt = prompt_add(PROMPT, &nfpr, 1);
	i = *cur - *cmd;
	len = 0;
	if (ret_prompt == -3 || ret_prompt == -1)
		ft_strdel(&nfpr);
	if (ret_prompt == -3 || ret_prompt == -1)
		return (-1);
	if (nfpr && nfpr[0] != '\n')
	{
		len = ft_strlen(nfpr);
		(*cmd) = ft_strjoin_free(*cmd, nfpr, 2);
		*cur = (*cmd) + i;
	}
	else
	{
		ft_strdel(&nfpr);
		return (-8);
	}
	return (read_parser(cmd, (*cmd) + i + len));
}
