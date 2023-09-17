#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>

int main(){
    char connectionMessage[1024] = "Connected to Server";

    // Create a socket
    int serverSocket  = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == -1){
        std::cerr << "Error Creating socket" << std::endl;
        return -1;
    }

    // Binding socket
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1){
        std::cerr << "Error Binding socket" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if(listen(serverSocket, 5) == -1){
        std::cerr << "Error listening for connections" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    // Accepting Incoming connections

    int clientSocket = accept(serverSocket, (struct sockaddr*) 0, (socklen_t *) 0);

    if(clientSocket == -1){
        std::cerr << "Error accepting client connection" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Client Connected..." << std::endl;

    send(clientSocket, connectionMessage, strlen(connectionMessage), 0);

    // Handle client communication

    char buffer[1024];
    char serverMessage[1024];

    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead;


    while(true){
        while(bytesRead = read(clientSocket, buffer, sizeof(buffer)) <= 0);
        std::cout << "Client: " << buffer << std::endl;
        
        // Send data to client
        std::cout << "Server: ";
        fgets(serverMessage, 1024, stdin);

        if(send(clientSocket, serverMessage, strlen(serverMessage), 0) == -1){
            std::cerr << "Message not sent!" << std::endl;
            return -1;
        }

        // Clear Buffers
        memset(buffer, 0, sizeof(buffer));
        memset(serverMessage, 0, sizeof(serverMessage));
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}