#include "tcp.h"


int main(){
    char connectionMessage[1024] = "Connected to Server";
    int serverSocket = Socket(AF_INET, SOCK_STREAM, 0);

    SA_IN serverAddress, clientAddress;
    serverAddress.sin_port = 8080;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    Bind(serverSocket, (SA*) &serverAddress, sizeof(serverAddress));

    Listen(serverSocket, 2);


    while(true){
        printf("Server listening to Port 8080...\n");

        int clientAddressLength = sizeof(clientAddress);
        int clientSocket = Accept(serverSocket, (struct sockaddr *) &clientAddress, (socklen_t *) &clientAddressLength);

        Send(clientSocket, connectionMessage, strlen(connectionMessage), 0);

        printf("Connected\n");

        pthread_t clientThread;
        int *clientSocket_ptr = malloc(sizeof(int));
        (*clientSocket_ptr) = clientSocket;
        pthread_create(&clientThread, NULL, handleConnection, clientSocket_ptr);
    }

    close(serverSocket);
    
    return 0;
}