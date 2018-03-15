/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnfdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:24:58 by thugo             #+#    #+#             */
/*   Updated: 2017/10/31 18:28:13 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnfdup(char *s, size_t len)
{
	char	*dup;

	if (!s)
		return (NULL);
	dup = ft_strndup(s, len);
	free(s);
	return (dup);
}
