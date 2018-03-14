/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_profonde_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 09:54:52 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 12:05:17 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		**cpy_argv_process(char **argv)
{
	char	**new;
	size_t	size;
	size_t	i;

	if (argv == NULL || argv[0] == NULL)
		return (NULL);
	size = ft_tab2dlen((const void**)(argv)) + 1;
	new = (char**)ft_memalloc(sizeof(char*) * size);
	i = 0;
	while (i < size)
	{
		new[i] = ft_memdup(argv[i], sizeof(char) * (ft_strlen(argv[i]) + 1));
		i++;
	}
	return (new);
}

t_process	*cpy_profonde_process(t_process *src)
{
	t_process	*new;

	new = (t_process*)ft_memalloc(sizeof(t_process));
	ft_memcpy(new, src, sizeof(t_process));
	new->argv = cpy_argv_process(src->argv);
	return (new);
}
