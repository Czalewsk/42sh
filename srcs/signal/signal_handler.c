/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:55:11 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/18 19:51:30 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_signal.h"

volatile char			g_new_prompt = 0;

static unsigned	long	g_signal_mask;

/*
**Variable qui defini si un signal doit etre gere par le signal handler
*/

static const char	g_signal_interrupt[MAX_NB_SIGNAL] = {
	[SIGCHLD] = 17,
	[SIGTSTP] = 7,
	[SIGTTIN] = 77,
	[SIGWINCH] = 1,
	[SIGCONT] = 7,
	[SIGQUIT] = 1};

/*
**Variable qui permet de stocke les fonctions a appeler dans le signl handler
** si la fonction est trop longue laisse la case a NULL et renseigner la
** dans le signal manager
*/

static void	(*const g_signal_fct[MAX_NB_SIGNAL])(void) = {
	[SIGCHLD] = &signal_sigchld,
	[SIGTSTP] = &signal_sigtstp,
	[SIGTTIN] = &signal_sigttin,
	[SIGWINCH] = &sigwinch,
	[SIGCONT] = &signal_sigcont,
	[SIGQUIT] = &signal_avoid};

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
	sigset_t					block_mask;
	struct sigaction			action;

	action.sa_sigaction = &signal_sigint;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&block_mask);
	i = -1;
	while (++i < MAX_NB_SIGNAL)
		if (g_signal_interrupt[i])
			sigaddset(&block_mask, i);
	sigaddset(&block_mask, SIGINT);
	action.sa_mask = block_mask;
	sigaction(SIGINT, &action, NULL);
	action.sa_sigaction = &signal_handler;
	action.sa_flags |= SA_RESTART;
	i = -1;
	while (++i < MAX_NB_SIGNAL)
		if (g_signal_interrupt[i] && sigaction(i, &action, NULL))
			exit(sh_error(EXIT_FAILURE, 1, &termcaps_restore_tty, 1,
						"Error in sigaction\n"));
}

inline		char		signal_manager(void)
{
	char	i;

	if (!g_signal_mask)
		return (0);
	i = -1;
	while (g_signal_mask && ++i < MAX_NB_SIGNAL)
		if (g_signal_mask & (1 << i))
		{
			g_signal_mask &= ~(1 << i);
			if (g_signal_mask_fct[(int)i])
				g_signal_mask_fct[(int)i]();
		}
	return (1);
}
