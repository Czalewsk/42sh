/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:08:18 by bviala            #+#    #+#             */
/*   Updated: 2017/11/28 15:49:46 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_getenv_addr(char **env, char *elem)
{
	int	len;
	int	len_path;

	if (!elem || !env)
		return (NULL);
	len = ft_strlen(elem);
	while (*env)
	{
		len_path = 0;
		while (((*env) + len_path) && *((*env) + len_path) != '=')
			len_path++;
		if (ft_strcmp(*env, elem) == '=' && len == len_path)
			return (env);
		env++;
	}
	return (NULL);
}

char	*ft_getenv(char **env, char *elem)
{
	int	len;
	int	len_path;

	if (!elem || !env)
		return (NULL);
	len = ft_strlen(elem);
	while (*env)
	{
		len_path = 0;
		while (((*env) + len_path) && *((*env) + len_path) != '=')
			len_path++;
		if (ft_strcmp(*env, elem) == '=' && len == len_path)
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}
