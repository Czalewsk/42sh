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

	nfpr = NULL;
	prompt_add(PROMPT, &nfpr);
	i = cur - (*cmd);
	(*cmd) = ft_strjoin_free(*cmd, nfpr, 2);
	return (read_parser(cmd, (*cmd) + i));
}