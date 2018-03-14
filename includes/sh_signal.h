/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 09:45:07 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/11 18:45:24 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SH_SIGNAL_H
# define __SH_SIGNAL_H

# include <signal.h>

# define MAX_NB_SIGNAL (32 + 1)
# define CHECK_BIT(x, n) (x & (1 << n))

extern volatile char	g_new_prompt;

extern t_read		*g_save_info;
extern t_buf		*g_save_cmd;

void					signal_handler(int sig, siginfo_t *siginfo,
		void *context);
void					signal_handler_init(void);
char					signal_manager(void);
void					signal_sigchld(void);
void					signal_sigtstp(void);
void					signal_sigttou(void);
void					signal_sigttin(void);
void					signal_sigint(int sig, siginfo_t *siginfo,
		void *context);
void					sigwinch(void);
void					signal_avoid(void);

#endif
