/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 20:00:43 by thugo             #+#    #+#             */
/*   Updated: 2017/04/05 06:38:25 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include "libunit_types.h"
#include "libunit_internal.h"

void	print_header(char *name)
{
	printf("\e[1m/*****************************\\\n");
	printf("|***********LIBUNIT***********|\n");
	printf("\\*****************************/\n");
	printf("%s\n\n\e[0m", name);
}

void	print_test(int status, char *name)
{
	char	status_str[50];

	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		strcpy(status_str, "\e[32mOK\e[0m");
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		strcpy(status_str, "\e[31mKO\e[0m");
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_BADEXE)
		strcpy(status_str, "\e[31mBAD EXE\e[0m");
	else if (WIFEXITED(status))
		sprintf(status_str, "\e[31mUNKN EXIT (%i)\e[0m", WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGABRT)
		strcpy(status_str, "\e[31mABRT\e[0m");
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGBUS)
		strcpy(status_str, "\e[31mBUSE\e[0m");
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
		strcpy(status_str, "\e[31mSEGV\e[0m");
	else if (WIFSIGNALED(status))
		sprintf(status_str, "\e[31mUNKN SIG (%u)\e[0m", WTERMSIG(status));
	else
		strcpy(status_str, "\e[33mUNKN\e[0m");
	printf(">\t%s : [%s]\n", name, status_str);
}

void	print_total(int valid, int total)
{
	printf("\e[%sm%i / %i\e[0m tests checked.\n", valid == total ? "32" : "31",
		valid, total);
}
