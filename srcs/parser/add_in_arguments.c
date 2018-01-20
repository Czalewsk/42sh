/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_in_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:31:29 by maastie           #+#    #+#             */
/*   Updated: 2018/01/11 16:31:29 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	**realloc_argv(char **argv, char *to_add, int s)
{
	char	**new;
	int		i;

	if ((new = (char **)malloc(sizeof(char *) * s)) == NULL)
		return (NULL);
	i = 0;
	while (argv && argv[i])
	{
		new[i] = ft_strdup(argv[i]);
		free(argv[i]);
		new[++i] = NULL;
	}
	new[i] = ft_strdup(to_add);
	new[++i] = NULL;
	free(argv);
	return (new);
}

char	**get_new_argv(char **argv, char *to_add)
{
	int		i;

	i = 0;
	if (!argv)
	{
		if ((argv = (char **)malloc(sizeof(char *) * 1)) == NULL)
			return (NULL);
		argv[0] = ft_strdup(to_add);
		argv[1] = NULL;
		return (argv);
	}
	while (argv && argv[i++]);
	return (argv = realloc_argv(argv, to_add, ++i));
}

t_tree	*add_in_arguments(t_tree *clist, t_job *job)
{
	job->first_process->argv = get_new_argv(job->first_process->argv, clist->token.str);
	return (clist->right);
}