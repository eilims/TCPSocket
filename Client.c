//
// Created by DanielB on 5/6/2018.
//

#include "Client.h"

int main(int argc, char** argv){
    int i;
    int control;
    int stringIsValid;
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
    stringIsValid = 0;
    printf("Enter 0 as the first character to exit\n");
    while(control)
     {
	stringIsValid = 0;
        printf("Please enter a string to transmit or 0 to exit: ");
	fgets(data, 100, stdin);
	while(!stringIsValid)
	  {
	     if((int)data[0] == 10)
	       {
		  printf("Please enter at least one character: ");
		  fgets(data, 100, stdin);
	       } else 
	       {
		  stringIsValid = 1;
	       }
	  }
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
	     if(send(socketDescriptorReference, data, strlen(data) - 1, 0) < 0) printf("Error Sending\n");
	     bufferPointer = buffer;
	     bytesReceived = recv(socketDescriptorReference, bufferPointer, maxBytesToRead, 0);
//	     while(bytesReceived > 0)
//	       {
//		  bufferPointer += bytesReceived;
//		  maxBytesToRead -= bytesReceived;
//		  bytesReceived = recv(socketDescriptorReference, bufferPointer, maxBytesToRead, 0);
//	       }
	     printf("Data Accepted. Number of Bytes Received: %d\n", buffer[0]);     
	  }
	else 
	  {
	     control = 0;  
	  }
	close(socketDescriptorReference);
	 
	
     }
   
   
    exit(0);
}

