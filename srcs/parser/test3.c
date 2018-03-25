/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 16:56:06 by maastie           #+#    #+#             */
/*   Updated: 2018/03/24 16:56:20 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
extern int errno;
/*
**   Simulation de la commande :
**   ls . ESFesegf 2&>1 1>&- | cat -e
*/  
int     main(void)
{
    int     stdin;
    int     stdout;
    int     stderr;
    int     pid;
    int     p[2];
    stdin = STDIN_FILENO;
    stdout = STDOUT_FILENO;
    stderr = STDERR_FILENO;
    pipe(p);
    pid = fork();
    if (!pid)
    {
        /* Je m'occupe de la redirection des pipes en 1er et
		** ferme l'autre coté du pipe */
        if ((stdout = dup2(p[1], stdout)) < 0)
            printf("Erreur dup22: %s\n", strerror(errno));
        if (close(p[0]) < 0)
            printf("Erreur close2: %s\n", strerror(errno));
        /* Je duplique la stdout et remplace la sterr */
        if (dup2(2, 1) < 0)
            printf("Erreur dup0: %s\n", strerror(errno));
        if ((dup2(stderr, STDERR_FILENO)) < 0)
            printf("Erreur dup21: %s\n", strerror(errno));
        /* Je close le fd 1 */
        if (close(STDOUT_FILENO) < 0)
            printf("Erreur close1: %s\n", strerror(errno));
        /* J'execute la commande  "ls . ESFesegf" */
        execve("/bin/ls", (char*[4]){"ls", ".", "ESFesegf", NULL} , NULL);
        printf("Erreur exec1:%s\n", strerror(errno));
        exit(1);
    }
    else
    {
        pid = fork();
        if (!pid)
        {
            /* Je m'occupe de la redirection des pipes en 1er et
			** ferme l'autre coté du pipe */
            if ((dup2(p[0], stdin)) < 0)
                printf("Erreur dup23: %s\n", strerror(errno));
            if (close(p[1]) < 0)
                printf("Erreur close2: %s\n", strerror(errno));
            /* J'execute la commande  "cat -e" */
            execve("/bin/cat", (char*[3]){"cat", "-e", NULL} , NULL);
            printf("Erreur exec2:%s\n", strerror(errno));
            exit(1);
        }
    }
    close(p[0]);
    close(p[1]);
    return (0);
}
