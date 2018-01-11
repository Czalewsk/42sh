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

char	**realloc_argv(char **argv, int s)
{
	char	**new;
	int		i;

	if ((new = (char **)malloc(sizeof(char *) * s)) == NULL)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		new[i] = argv[i];
		new[++i] = NULL;
	}
	free(argv);
	return (new);
}

char	**get_new_argv(char **argv)
{
	int		i;

	i = 0;
	if (!argv)
	{
		if ((argv = (char **)malloc(sizeof(char *) * 1)) == NULL)
			return (NULL);
		return (argv);
	}
	while (argv && argv[i++]);
	return (argv = realloc_argv(argv, ++i));
}

t_tree	*add_in_arguments(t_tree *clist, t_job *job)
{
	int	i;

	job->first_process->argv = get_new_argv(job->first_process->argv);
	i = 0;
	while (job->first_process->argv && job->first_process->argv[i++]);
	job->first_process->argv[i] = clist->token.str;
	return (clist);
}