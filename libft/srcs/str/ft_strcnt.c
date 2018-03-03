/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 03:09:04 by thugo             #+#    #+#             */
/*   Updated: 2018/02/03 03:20:12 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  Renvoi la premiere occurence trouve dans s d'un des caractere de sfind.
*/

char       *ft_strcnt(const char *s, const char *sfind)
{
    if (!s || !sfind)
        return (NULL);
    while (*s)
    {
        if (ft_strchr(sfind, *s))
            return ((char *)s);
        ++s;
    }
    return (NULL);
}
