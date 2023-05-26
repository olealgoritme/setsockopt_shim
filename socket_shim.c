#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

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
