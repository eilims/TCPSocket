//
// Created by DanielB on 5/6/2018.
//

#include "Client.h"

int main(int argc, char** argv){
    int i;
    int socketDescriptor;
    int socketDescriptorReference;
    char* data;
    char buffer[256];
    char* bufferPointer = buffer;
    int bytesToRead = 0;
    int maxBytesToRead = sizeof(buffer);
    int bytesReceived = 0;
    char* serverName;
    struct sockaddr_in serverAddr;
    int clientAddressLength;

    serverName = argv[1];
    data = argv[2];

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, serverName,&serverAddr.sin_addr);
    serverAddr.sin_port = htons(8080);

    if((socketDescriptorReference = socket(PF_INET, SOCK_STREAM, 0) < 0)){
        perror("Error: Creating Socket Failed\n");
        exit(1);
    }

    if((connect(socketDescriptorReference, &serverAddr, sizeof(serverAddr))) < 0){
        perror("Error: Connection Failed\n");
        exit(1);
    }

    send(socketDescriptorReference, data, strlen(data), 0);

    close(socketDescriptorReference);

    exit(0);
}

