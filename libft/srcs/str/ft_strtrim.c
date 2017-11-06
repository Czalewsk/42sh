/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:57:18 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:57:20 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int	i;
	int	len;
	int	start;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] == '\n' || s[i] == '\t' || s[i] == ' '))
		i++;
	if (s[i] == '\0')
		return (ft_strnew(0));
	start = i;
	i = ft_strlen((char*)s) - 1;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == ' ')
		i--;
	len = i - start + 1;
	return (ft_strsub(s, start, len));
}
