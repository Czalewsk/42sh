/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 09:45:07 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/02 11:31:53 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SIGNAL_H
# define __SIGNAL_H

# include <signal.h>

# define MAX_NB_SIGNAL (32 + 1)
# define CHECK_BIT(x, n) (x & (1 << n))

void					signal_handler(int sig, siginfo_t *siginfo,
		void *context);
void					signal_handler_init(void);
void					signal_manager(void);

#endif
