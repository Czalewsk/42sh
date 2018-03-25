/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 16:57:06 by maastie           #+#    #+#             */
/*   Updated: 2018/03/24 16:57:25 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
extern int errno;
int     main(void)
{
    int     fd_open;
    int     fd1;
    int     fd2;
    fd1 = 100;
    fd2 = 154;
    if ((fd_open = open("./ok", O_RDONLY)) < 0)
        printf("Erreur open: %s\n", strerror(errno));
    if ((dup2(fd_open, fd1)) < 0)
        printf("Erreur dup21: %s\n", strerror(errno));
    if ((dup2(dup(fd1), fd2)) < 0)
        printf("Erreur dup22: %s\n", strerror(errno));
    if ((dup2(fd2, STDIN_FILENO)) < 0)
        printf("Erreur dup23: %s\n", strerror(errno));
    execve("/bin/cat", (char*[2]){"cat", NULL} , NULL);
    printf("Erreur exec:%s\n", strerror(errno));
    return (1);
}