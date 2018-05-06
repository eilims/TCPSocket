//
// Created by DanielB on 5/6/2018.
//

#include "Server.h"

int main(){

    int i;
    int socketDescriptor;
    int socketDescriptorReference;
    char buffer[256];
    char* bufferPointer = buffer;
    int bytesToRead = 0;
    int maxBytesToRead = sizeof(buffer);
    int bytesReceived = 0;
    int maxWaitingClients = 4;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int clientAddressLength;

    //Creating local socket address for server
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8080);

    //Creating listening socket
    socketDescriptor = socket(PF_INET, SOCK_STREAM, 0);
    if(socketDescriptor < 0){
        perror("Error: Creating socket failied\n");
        exit(1);
    }

    //bind listen socket to local socket address
    if(bind(socketDescriptor, &serverAddr, sizeof(serverAddr)) < 0){
        perror("Error: Binding failed\n");
        exit(1);
    }

    if(listen(socketDescriptor, maxWaitingClients)){
        perror("Error: Listening Failed\n");
        exit(1);
    }

    while(1){
        bufferPointer = buffer;
        maxBytesToRead = sizeof(buffer);
        socketDescriptorReference = accept(socketDescriptor, &clientAddr, &clientAddressLength);
        if(socketDescriptorReference < 0){
            perror("Error: Accepting failed\n");
            exit(1);
        }
        //printf("Im here\n");
        bytesReceived = recv(socketDescriptorReference, bufferPointer, maxBytesToRead, 0);
        while(bytesReceived > 0){
            bufferPointer += bytesReceived;
            maxBytesToRead -= bytesReceived;
            bytesReceived = recv(socketDescriptorReference, bufferPointer, maxBytesToRead, 0);
	}

        for(i = 0; i < sizeof(buffer) - maxBytesToRead; i++){
            printf("Index: %d Data: %c\n", i, buffer[i]);
        }

        close(socketDescriptorReference);
    }

}

