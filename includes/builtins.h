/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:13:08 by bviala            #+#    #+#             */
/*   Updated: 2018/03/14 18:51:01 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BUILTINS_H
# define __BUILTINS_H

# include "ft_sh.h"

int		builtin_history(t_process *p);
int		builtin_export(t_process *p, int argc, char **argv, char **env);
int		builtin_unsetenv(t_process *p, int argc, char **argv, char **env);
int		builtin_setenv(t_process *p, int argc, char **argv, char **env);
int		builtin_cd(t_process *p, int argc, char **argv, char **env);

#endif
