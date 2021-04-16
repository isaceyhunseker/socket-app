#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2323
#define BUFFER_LENGHT 10

void main(){

	int sockfd;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;
	char buffer[BUFFER_LENGHT], msgBuffer[BUFFER_LENGHT] = "sea";

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("[+]Server Socket Created Sucessfully.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to Port number %d.\n", 2323);

	listen(sockfd, 5);
	printf("[+]Listening...\n");
    memset(buffer, '\0', sizeof(char)*BUFFER_LENGHT);
    
	while(newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size)){
		while (recv(newSocket, buffer, BUFFER_LENGHT, 0)>0) {
			printf("Message Received: %s", buffer);
			if(buffer[0] == 'q' && buffer[1] == 'u')
				break;
            send(newSocket, msgBuffer, strlen(msgBuffer), 0);    
			memset(buffer, '\0', sizeof(char)*BUFFER_LENGHT);}
		printf("[+]Closing the connection.\n");
		shutdown(newSocket, SHUT_RDWR);
		exit(0);
	}
}
