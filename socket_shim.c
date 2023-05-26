#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <sys/socket.h>

int (*shim_socket) (int domain, int type, int protocol) = NULL;

int socket (int __domain, int __type, int __protocol)
{
    int sockfd;
    int option = 1;

    /* switch run-time address of object handle for socket() */
    shim_socket = dlsym(RTLD_NEXT, "socket");

    /* force SO_REUSEADDR to re-use bind() without waiting for TIME_WAIT state to complete */
    sockfd = shim_socket(__domain, __type, __protocol);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    /* ret with shimmed socket() */
    return sockfd;
}
