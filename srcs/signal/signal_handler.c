/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:55:11 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/02 11:48:53 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_signal.h"

static unsigned	long	g_signal_mask;

/*
**Variable qui defini si un signal doit etre gere par le signal handler
*/

static const	char	g_signal_interrupt[MAX_NB_SIGNAL] = {[SIGINT] = 0};

/*
**Variable qui permet de stocke les fonctions a appeler dans le signl handler
** si la fonction est trop longue laisse la case a NULL et renseigner la
** dans le signal manager
*/

static			void	(*const g_signal_fct[MAX_NB_SIGNAL])(void) =
{[1] = NULL};

/*
** Variable qui stock les fonctions appelle par le signal manager dans la boucle
**  principale
*/

static			void	(*const g_signal_mask_fct[MAX_NB_SIGNAL])(void) =
{NULL};

void					signal_handler(int sig, siginfo_t *siginfo,
		void *context)
{
	(void)siginfo;
	(void)context;
	if (g_signal_fct[sig])
		g_signal_fct[sig]();
	else
		g_signal_mask |= (1 << sig);
}

void					signal_handler_init(void)
{
	int							i;
	const	struct sigaction	action = {.sa_sigaction = &signal_handler,

	.sa_flags = SA_SIGINFO};
	i = -1;
	while (++i <= MAX_NB_SIGNAL)
		if (g_signal_interrupt[i] && sigaction(i, &action, NULL))
			exit(sh_error(EXIT_FAILURE, 1, NULL, 1, "Error in sigaction\n"));
}

inline		void		signal_manager(void)
{
	char	i;

	if (!g_signal_mask)
		return ;
	i = -1;
	while (g_signal_mask && ++i <= MAX_NB_SIGNAL)
		if (g_signal_mask_fct[(int)i])
		{
			g_signal_mask &= ~(1 << i);
			g_signal_mask_fct[(int)i]();
			break ;
		}
}
