/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:24:01 by bviala            #+#    #+#             */
/*   Updated: 2017/11/28 17:32:33 by czalewsk         ###   ########.fr       */
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

#endif
