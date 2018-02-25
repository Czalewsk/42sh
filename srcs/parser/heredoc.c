/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 21:03:58 by maastie           #+#    #+#             */
/*   Updated: 2018/02/24 21:03:59 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			read_hr(char *hr, char *ref)
{
	if (ft_strlen(hr) -1 == 0)
		return (-1);
	else if (ft_memcmp(hr, ref, ft_strlen(hr) -1) != 0)
		return (-1);
	return (0);
}

t_tree		*here_doc(t_process *p, t_tree *c)
{
	char	*hr;
	int		asd[2];

	(void)p;
	if (pipe(asd) == -1)
 		return ((void *)1);// return (sh_error)
 	hr = NULL;
	prompt_add("> ", &hr);
 	while (read_hr(hr, c->right->token.str) != 0)
 	{
 		ft_putstr_fd(hr, asd[1]);
		ft_strdel(&hr);
	 	prompt_add("> ", &hr);
 	}
 	ft_strdel(&hr);
 	close(asd[1]);
 	dup2(asd[0], STDIN_FILENO);
	close(asd[0]);
 	return (c->right->right);
}
