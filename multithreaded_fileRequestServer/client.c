#include "tcp.h"

int main(){

    char clientConnectionMessage[1024] = "Connected to Client";
    

    int clientSocket = Socket(AF_INET, SOCK_STREAM, 0);

    SA_IN serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = 8080;
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    Connect(clientSocket, (SA*) &serverAddress, sizeof(serverAddress));

    size_t len;
    ssize_t n;
    char buffer[BUFFSIZE];
    // Connection Est.

    n = Recv(clientSocket, buffer, BUFFSIZE, 0);
    if(n > 0){
        printf("%s\n", buffer);
    }

    // Get File Path from the user
    printf("Enter Path: ");
    fgets(buffer, BUFFSIZE, stdin);
    len = strlen(buffer);

    // Remove newline character
    if(buffer[len - 1] == '\n')
        len--;
    
    printf("Sending Path...\n");
    // Send path to Server
    Send(clientSocket, buffer, len, 0);

    // Keep reading from Pipe
    printf("Content of file:\n");
    while((n = Recv(clientSocket, buffer, BUFFSIZE, 0)) > 0){
        // Writing to STDOUT
        Write(STDOUT_FILENO, buffer, n);
    }
    
    close(clientSocket);
    pause();
    return 0;
}






/*

char buffer[1024] = {0};
    ssize_t serverMessage;
    while(true){
        while(serverMessage = Recv(clientSocket, buffer, sizeof(buffer), 0) <= 0);
        buffer[serverMessage - 1] = 0;
        printf("Server: %s\n", buffer);
        bzero(buffer, sizeof(buffer));

        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        if(strncasecmp(buffer, "END", 3) == 0){ break; }
        Send(clientSocket, buffer, strlen(buffer), 0);
        bzero(buffer, sizeof(buffer));
    }
*/