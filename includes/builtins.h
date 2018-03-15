/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:13:08 by bviala            #+#    #+#             */
/*   Updated: 2018/03/15 17:20:38 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BUILTINS_H
# define __BUILTINS_H

# include "ft_sh.h"

int		builtin_export(t_process *p, int argc, char **argv, char **env);
int		builtin_history(t_process *p, int argc, char **argv, char **env);
int		built_h_clear_one(char *res, char **argv, t_process *p);
int		built_h_save_one(char **argv, t_process *p);
int		builtin_unsetenv(t_process *p, int argc, char **argv, char **env);
int		builtin_setenv(t_process *p, int argc, char **argv, char **env);
int		builtin_exit(t_process *p, int argc, char **argv, char **env);
int		builtin_echo(t_process *p, int argc, char **argv, char **env);
char	*change_expoint_h(char *str, char *old, char *new);
void	update_expoint_h(t_ldl_head *history, char *save);	
#endif
