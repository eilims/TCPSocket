//
// Created by DanielB on 5/6/2018.
//

#include "Client.h"

int main(int argc, char** argv){
    int i;
    int control;
    int socketDescriptor;
    int socketDescriptorReference;
    char data[100];
    char buffer[256];
    char* bufferPointer = buffer;
    int bytesToRead = 0;
    int maxBytesToRead = sizeof(buffer);
    int bytesReceived = 0;
    char* serverName;
    struct sockaddr_in serverAddr;
    int clientAddressLength;

    serverName = argv[1];
    control = 1; 
    printf("Enter 0 as the first character to exit\n");
    while(control)
     {
        printf("Please enter a string to transmit or 0 to exit: ");
	fgets(data, 100, stdin);
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, serverName,&serverAddr.sin_addr);
	serverAddr.sin_port = htons(8080);
	
	socketDescriptorReference = socket(PF_INET, SOCK_STREAM, 0);
	if(socketDescriptorReference < 0){
	   perror("Error: Creating Socket Failed\n");
	   exit(1);
	}
	
	if((connect(socketDescriptorReference, &serverAddr, sizeof(serverAddr))) < 0){
	   perror("Error: Connection Failed\n");
	   exit(1);
	}
	
	if(data[0] != '0')
	  {
	     send(socketDescriptorReference, data, strlen(data) - 1, 0);
	     close(socketDescriptorReference);
	  }
	else 
	  {
	   control = 0;  
	  }
	
     }
   
   
    exit(0);
}

