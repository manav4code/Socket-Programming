#include "tcp.h"

// Wrapper of Socket
int Socket(int domain, int type, int protocol){
    int socketDescriptor;

    if( (socketDescriptor = socket(domain, type, protocol)) < 0){
        perror("Socket not created");
        exit(EXIT_FAILURE);
    }

    return socketDescriptor;
}

// Wrapper of bind
int Bind(int fd, struct sockaddr *socketAddress, socklen_t socketSize){
    if( bind(fd, socketAddress, socketSize) == -1){
        perror("Unable to bind");
        close(fd);
        exit(EXIT_FAILURE);
    }
}

// Wrapper of listen
int Listen(int fd, int n){
    if( listen(fd, n) == -1){
        perror("Error while listen");
        close(fd);
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Accept(int fd, struct sockaddr *socketAddress, socklen_t *addrLen){
    int socketDescriptor;

    if( (socketDescriptor = accept(fd, socketAddress, addrLen)) == -1){
        perror("Unable to accept");
        close(fd);
        exit(EXIT_FAILURE);
    }

    return socketDescriptor;
}

// Wrapper for Connect
int Connect(int fd, struct sockaddr *socketAddress, socklen_t addrLen){
    if(connect(fd, socketAddress, addrLen) == -1){
        perror("Cannot connect");
        exit(EXIT_FAILURE);
    }
}

// Wrapper for close
void Close(int fd){
    if( close(fd) == -1){
        perror("Unable to close");
        exit(EXIT_FAILURE);
    }
}

ssize_t Read(int fd, char *buf, size_t nbytes){
    ssize_t readBytes;

    if( (readBytes = read(fd, buf, nbytes)) == -1){
        perror("Cannot read the socket");
        exit(EXIT_FAILURE);
    }

    return readBytes;
}

void Write(int fd, const void* buf, size_t nbytes){
    if(write(fd, buf, nbytes) == -1){
        perror(strerror(errno));
        exit(errno);
    }
}

ssize_t Recv(int fd, char *buf, size_t nbytes, int flag){
    ssize_t readBytes;

    if( (readBytes = recv(fd, buf, nbytes, flag)) == -1){
        perror("Cannot read the socket");
        exit(EXIT_FAILURE);
    }

    return readBytes;
}

ssize_t Send(int fd, void* buf, size_t n, int flag){
    ssize_t sendBytes;

    if( (sendBytes = send(fd, buf, n, flag)) == -1){
        perror("Cannot send through socket");
        exit(EXIT_FAILURE);
    }

    return sendBytes;
}

//----------END OF WRAPPER FUNCTIONS--------------


//---------------FUNCTIONS------------------------

// Function to handle client on server-side
void* handleConnection(void* clientSocket_ptr){
    int clientSocketDescriptor = (*(int*)clientSocket_ptr);
    free(clientSocket_ptr);

    int filefd;
    ssize_t n;
    char buffer[BUFFSIZE + 1];

    // Read PATH from Pipe
    if( (n = Recv(clientSocketDescriptor, buffer, BUFFSIZE, 0)) == 0){
        perror("EOF while reading the PATH");
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';

    if( (filefd = open(buffer, O_RDONLY)) < 0){
        // Write back the error msg to client
        snprintf(buffer + n, sizeof(buffer) - n, ": can't open file, %s\n", strerror(errno));

        n = strlen(buffer);
        Write(clientSocketDescriptor, buffer, n);
    }
    else{
        // Read file till EOF and Write to Pipe
        while( (n = Read(filefd, buffer, BUFFSIZE)) > 0){
            Write(clientSocketDescriptor, buffer, n);
            msleep(100);
        }
    }

    // Close file
    Close(filefd);
    Close(clientSocketDescriptor);
    pthread_exit(NULL);
}