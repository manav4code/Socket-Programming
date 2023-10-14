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

    char clientBuffer[BUFFSIZE];
    ssize_t clientMessage;

    while(true){
        clientMessage = Recv(clientSocketDescriptor, clientBuffer, sizeof(clientBuffer), 0);
        
        // EOF - Client Socket is closed from client side
        if(clientMessage == 0){ break; }
        clientBuffer[clientMessage - 1] = 0;
        printf("Client: %s\n", clientBuffer);
        // if(strncasecmp(clientBuffer, "END", 3) == 0){ break; }
        bzero(clientBuffer, sizeof(clientBuffer));
        
        
        printf("Server: ");
        fgets(clientBuffer, sizeof(clientBuffer), stdin);
        Send(clientSocketDescriptor, clientBuffer, strlen(clientBuffer), 0);
        bzero(clientBuffer, sizeof(clientBuffer));
    }
    printf("Client Disconnected...\n");
    Close(clientSocketDescriptor);
    pthread_exit(NULL);
}