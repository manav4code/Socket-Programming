#ifndef TCP_H

#define TCP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>


typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;


#define bzero(buffer, n) memset(buffer, 0, n)
#define BUFFSIZE 4096

static const char* CONNECTIONEND = "END";


// Wrapper of socket
int Socket(int domain, int type, int protocol);

// Wrapper of bind
int Bind(int fd, struct sockaddr *socketAddress, socklen_t socketSize);

// Wrapper of listen
int Listen(int fd, int n);

// Wrappe of accept
int Accept(int fd, struct sockaddr *socketAddress, socklen_t *addrLen);

// Wrapper for Read
ssize_t Read(int fd, char *buf, size_t nbytes);

// Wraper for recv
ssize_t Recv(int fd, char *buf, size_t nbytes, int flag);

// Wrapper for send
ssize_t Send(int fd, void* buf, size_t n, int flag);

// Wrapper for Connet
int Connect(int fd, struct sockaddr *socketAddress, socklen_t addrLen);

// Wrapper for close
void Close(int fd);

// Function to handle client on server-side
void* handleConnection(void* clientSocket_ptr);
#endif
