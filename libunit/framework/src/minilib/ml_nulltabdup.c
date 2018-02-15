/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_nulltabdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 17:02:44 by thugo             #+#    #+#             */
/*   Updated: 2017/04/02 14:55:39 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	**ml_nulltabdup(char **src)
{
	char	**new;
	size_t	size;

	size = 0;
	while (src[size])
		++size;
	if (!(new = (char **)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	size = 0;
	while (src[size])
	{
		if (!(new[size] = strdup(src[size])))
			return (new);
		++size;
	}
	new[size] = NULL;
	return (new);
}
