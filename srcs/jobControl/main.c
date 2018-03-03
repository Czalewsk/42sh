/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:56:19 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 12:45:15 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
    int pid;
    int status;

    pid = fork();
    if (pid)
    {
        sleep(1);
        //kill(pid, 13);
        wait(&status);
        if (WIFSIGNALED(status))
            printf("%s: %d", strsignal(WTERMSIG(status)), WTERMSIG(status));
        else if (status == 0)
            printf("Done");
        else
            printf("exit: %d", WEXITSTATUS(status));
    }
    else
    {
        sleep(2);
        exit(48);
    }
    
    return (0);
}