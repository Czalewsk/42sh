/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:28:37 by bviala            #+#    #+#             */
/*   Updated: 2018/01/11 19:13:48 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Donne une string (name) a trouver dans une $variable d'environnement (var)
** specifiee de l'environnement (env) fourni en parametre.
** Si name est trouve, on save la path complete dans (save).
** Les valeurs de retour sont les suivantes :
** -1 : wrong args en parametres			(save == NULL)
**  0 : fichier non trouve.					(save == NULL)
**  1 :	fichier existe et executable.			(save)
**  2 :	fichier existe et permission denied.	(save)
**  3 :	fichier existe et est un dir.			(save)
*/

static char	**get_tab_path(char **env, char *name, char *var)
{
	char	**tab;
	int		i;

	if (!(tab = ft_strsplit(ft_getenv(env, var), ':')))
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		tab[i] = ft_strjoin_free(tab[i], "/", 0);
		tab[i] = ft_strjoin_free(tab[i], name, 0);
		i++;
	}
	return (tab);
}

static int	check_ret_path(char **tab, int ret, char **save, struct stat stat)
{
	int		i;
	char	*tmp;

	if (!ret || (i = 0))
		return (0);
	tmp = NULL;
	while (tab && tab[i])
	{
		if ((lstat(tab[i], &stat) != -1))
		{
			if (S_ISREG(stat.st_mode))
				tmp = tab[i];
			else if (stat.st_mode & S_IFDIR)
			{
				*save = ft_strdup(tab[i]);
				return (3);
			}
		}
		i++;
	}
	if (tmp && (*save = ft_strdup(tmp)))
		return (2);
	return (0);
}

int			ft_getenv_status(char **env, char *name, char *var, char **save)
{
	char		**tab_path;
	int			i;
	struct stat	stat;
	int			ret;
	int			exist;

	if (!env || !name || !var || !(tab_path = get_tab_path(env, name, var)))
		return (-1);
	exist = 0;
	i = -1;
	while (tab_path && tab_path[++i])
	{
		if ((lstat(tab_path[i], &stat) != -1))
		{
			exist = 1;
			if (S_ISREG(stat.st_mode) && !access(tab_path[i], X_OK))
			{
				*save = ft_strdup(tab_path[i]);
				break ;
			}
		}
	}
	ret = (*save) ? 1 : check_ret_path(tab_path, exist, save, stat);
	tab_path ? free_tab2d(&tab_path) : NULL;
	return (ret);
}
