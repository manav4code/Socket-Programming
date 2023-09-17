#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstdio>

void throwError(const char* errorMessage){
    std::cerr << errorMessage << std::endl;
}

int main(){

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1){
        throwError("Error creating socket");
        return -1;
    }

    struct sockaddr_in serv_address;
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(8080);
    serv_address.sin_addr.s_addr = INADDR_ANY;

    if(connect(clientSocket, (struct sockaddr*) &serv_address, sizeof(serv_address)) < 0){
        throwError("Error connecting to the server");
        close(clientSocket);
        return -1;
    }

    std::cout << "Connected to server" << std::endl;

    char sendBuffer[1024];
    char receiveBuffer[1024];
    ssize_t serverMessage;

    do{
        // Wait for server message
        
        while(serverMessage = read(clientSocket, receiveBuffer, sizeof(receiveBuffer)) <= 0);
        std::cout << "Server: " << receiveBuffer << std::endl;
        memset(receiveBuffer, 0 , sizeof(receiveBuffer));
        
        // Send Client Message
        
        memset(sendBuffer, 0, sizeof(sendBuffer));
        std::cout << "Client: ";
        fgets(sendBuffer, 1024, stdin);
    } while (send(clientSocket, sendBuffer, sizeof(sendBuffer), 0) != -1);
    
    close(clientSocket);

    return 0;
}