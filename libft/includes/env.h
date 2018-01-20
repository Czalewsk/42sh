/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:24:01 by bviala            #+#    #+#             */
/*   Updated: 2018/01/11 17:37:24 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"

char	*ft_getenv(char **env, char *elem);
char	**ft_getenv_addr(char **env, char *elem);
void	ft_setenv(char *key, char *value, char ***env);
void	ft_env_cpy(char ***env);
void	ft_addenv(char *key, char *value, char ***env);
void	ft_printenv(char **env);
void	ft_unsetenv(char *key, char **env);
int		ft_getenv_status(char **env, char *name, char *var, char **save);
#endif
