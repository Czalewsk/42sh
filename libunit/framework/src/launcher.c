/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:26:51 by thugo             #+#    #+#             */
/*   Updated: 2017/04/21 06:19:12 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "libunit.h"
#include "libunit_internal.h"
#include "minilib.h"

extern char	**environ;

static int	exec_fn(int (*f)(void))
{
	int	status;

	if (fork() == 0)
	{
		if (!f())
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
	wait(&status);
	return (status);
}

static int	exec_fn_io(int (*f)(int, int))
{
	int		status;
	int		pipe_in[2];
	int		pipe_out[2];

	if (fork() == 0)
	{
		if (pipe(pipe_in) || pipe(pipe_out))
		{
			perror("libunit");
			exit(EXIT_FAILURE);
		}
		dup2(pipe_in[0], STDIN_FILENO);
		dup2(pipe_out[1], STDOUT_FILENO);
		close(pipe_in[0]);
		close(pipe_out[1]);
		if (!f(pipe_in[1], pipe_out[0]))
		{
			close(pipe_in[1]);
			close(pipe_out[0]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipe_in[1]);
			close(pipe_out[0]);
			exit(EXIT_FAILURE);
		}
	}
	wait(&status);
	return (status);
}


static int	exec_exe(t_unit_exe *exe)
{
	int		status_exe;
	int		status_fn;
	int		pipe_in[2];
	int		pipe_out[2];
	pid_t	pid_exe;

	if (pipe(pipe_in) || pipe(pipe_out))
	{
		perror("libunit");
		exit(EXIT_FAILURE);
	}
#ifdef __APPLE__
	fcntl(pipe_in[1], F_SETNOSIGPIPE, 1);
	fcntl(pipe_out[1], F_SETNOSIGPIPE, 1);
#endif
	if ((pid_exe = fork()) == 0)
	{
		dup2(pipe_in[0], STDIN_FILENO);
		dup2(pipe_out[1], STDOUT_FILENO);
		close(pipe_in[1]);
		close(pipe_out[0]);
		close(pipe_in[0]);
		close(pipe_out[1]);
		execve(exe->path, exe->argv, environ);
		exit(EXIT_BADEXE);
	}
	if (fork() == 0)
	{
		close(pipe_in[0]);
		close(pipe_out[1]);
		if (exe->fn(pipe_in[1], pipe_out[0], pid_exe))
		{
			close(pipe_in[1]);
			close(pipe_out[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipe_in[1]);
			close(pipe_out[0]);
			exit(EXIT_SUCCESS);
		}
	}
	close(pipe_in[0]);
	close(pipe_in[1]);
	close(pipe_out[0]);
	close(pipe_out[1]);
	wait(&status_exe);
	wait(&status_fn);
	if ((!WIFEXITED(status_exe) || WEXITSTATUS(status_exe) != EXIT_SUCCESS))
		return (status_exe);
	return (status_fn);
}

static int	exec_test(t_unit_test *test)
{
	int		status;

	if (test->ftype == FTYPE_FN)
		status = exec_fn(test->f.fn);
	else if (test->ftype == FTYPE_FN_IO)
		status = exec_fn_io(test->f.fn_io);
	else if (test->ftype == FTYPE_EXE)
		status = exec_exe(&(test->f.exe));
	else
		return (-1);
	print_test(status, test->name);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		return (0);
	return (-1);
}

void		free_tests(t_unit_tests *tests)
{
	t_ml_list	*curlauncher;
	t_ml_list	*nextlauncher;
	t_ml_list	*curtest;
	t_ml_list	*nexttest;

	curlauncher = tests->launchers;
	while (curlauncher)
	{
		curtest = ((t_unit_launcher *)curlauncher->content)->tests;
		while (curtest)
		{
			nexttest = curtest->next;
			free(((t_unit_test *)curtest->content)->name);
			free(curtest->content);
			free(curtest);
			curtest = nexttest;
		}
		nextlauncher = curlauncher->next;
		free(((t_unit_launcher *)curlauncher->content)->name);
		free(curlauncher->content);
		free(curlauncher);
		curlauncher = nextlauncher;
	}
	free(tests->name);
	free(tests);
}

/*
**	Execute et affiche tout les tests.
**	Return:
**		0: Tout les tests passent.
**		-1: 1 ou plusieurs test echouent.
*/

int			unit_launch_tests(t_unit_tests *tests)
{
	t_ml_list		*curlauncher;
	t_ml_list		*curtest;
	t_unit_test		*test;
	unsigned int	validtests;
	unsigned int	totaltests;

	validtests = 0;
	totaltests = 0;
	print_header(tests->name);
	curlauncher = tests->launchers;
	while (curlauncher)
	{
		printf("\e[1m%s:\e[0m\n", ((t_unit_launcher *)curlauncher->content)
			->name);
		curtest = ((t_unit_launcher *)curlauncher->content)->tests;
		while (curtest)
		{
			test = (t_unit_test *)curtest->content;
			if (!exec_test(test))
				++validtests;
			++totaltests;
			curtest = curtest->next;
		}
		curlauncher = curlauncher->next;
	}
	print_total(validtests, totaltests);
	free_tests(tests);
	return (validtests == totaltests ? 0 : -1);
}
