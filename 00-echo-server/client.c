#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2323
#define BUFFER_LENGHT 1024

void main(){
	
	int clientSocket;
	struct sockaddr_in serverAddr;
	char msgBuffer[BUFFER_LENGHT];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	printf("[+]Client Socket Created Sucessfully.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Connected to Server.\n");

	while(1) {
		printf("Enter a message, write 'qu' to close the chat: ");
		fgets(msgBuffer, 1024, stdin);
		send(clientSocket, msgBuffer, strlen(msgBuffer), 0);
		if(msgBuffer[0] == 'q' && msgBuffer[1] == 'u')
				break;
	}
	printf("[+]Closing the connection.\n");
	shutdown(clientSocket, SHUT_RDWR);
}
