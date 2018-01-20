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


char	*new_cmd_line(char *ref, char *new)
{
	char	*n;
	int		i;
	int		a;

	n = NULL;
	if ((n = (char *)malloc(sizeof(char) *
		(ft_strlen(ref) + ft_strlen(new)))) == NULL)
		return (NULL);
	i = 0;
	a = 0;
	while (ref && ref[i])
	{
		n[a] = ref[i++];
		n[++a] = '\0';
	}
	i = 0;
	while (new && new[i])
	{
		n[a] = new[i++];
		n[++a] = '\0';
	}
//	free(ref);
	return (n);
}

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