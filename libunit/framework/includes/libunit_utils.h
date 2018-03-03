/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:17:10 by thugo             #+#    #+#             */
/*   Updated: 2018/02/15 09:10:21 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_UTILS_H
# define LIBUNIT_UTILS_H

int		utils_getline(const int fd, char **line);
void	utils_purgefd(const int fd);
char	**utils_venvinit(void);
void	utils_venvdestroy(char **venv);
void	utils_venvadd(char ***venv, const char *key, const char *value);
char	*utils_venvget(char **venv, const char *key);

#endif
