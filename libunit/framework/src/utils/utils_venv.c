/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_venv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 07:35:55 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 09:10:29 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char	**venv_getaddress(char **venv, const char *key)
{
	char	*keyend;
	size_t	len;

	if (!venv || !key)
		return (NULL);
	if (!(len = strlen(key)))
		return (NULL);
	while (*venv)
	{
		keyend = strchr(*venv, '=');
		if (len == (size_t)(keyend - *venv) && !strncmp(key, *venv, len))
			return (venv);
		++venv;
	}
	return (NULL);
}

char		**utils_venvinit(void)
{
	char	**venv;

	if (!(venv = (char **)malloc(sizeof(char *))))
		exit(EXIT_FAILURE);
	*venv = NULL;
	return (venv);
}

void		utils_venvdestroy(char **venv)
{
	int		i;

	if (!venv)
		return ;
	i = -1;
	while (venv[++i])
		free(venv[i]);
	free(venv);
}

void		utils_venvadd(char ***venv, const char *key, const char *value)
{
	char	*str;
	char	**found;
	int		i;

	if (!venv || !*venv || !key || !value)
		return ;
	if (!(str = (char *)malloc(strlen(key) + strlen(value) + 2)))
		exit(EXIT_FAILURE);
	strcpy(str, key);
	strcat(str, "=");
	strcat(str, value);
	if ((found = venv_getaddress(*venv, key)))
	{
		free(*found);
		*found = str;
		return ;
	}
	i = 0;
	while ((*venv)[i])
		++i;
	if (!((*venv) = realloc(*venv, sizeof(char *) * (i + 2))))
		exit(EXIT_FAILURE);
	(*venv)[i] = str;
	(*venv)[i + 1] = NULL;
}

char		*utils_venvget(char **venv, const char *key)
{
	char	**found;

	if ((found = venv_getaddress(venv, key)))
		return (strchr(*found, '=') + 1);
	return (NULL);
}
