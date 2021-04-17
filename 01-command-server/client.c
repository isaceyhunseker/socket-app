#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2323
#define BUFFER_LENGHT 100

void main(){
	int clientSocket;
	struct sockaddr_in serverAddr;
	char msgBuffer[BUFFER_LENGHT], rcvBuffer[BUFFER_LENGHT];
	char *token;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	printf("[+]Client Socket Created Sucessfully.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Connected to Server.\n");
	memset(rcvBuffer, '\0', sizeof(char)*BUFFER_LENGHT);

	while(1) {
		printf("Enter command:(help to see all commands) ");
		fgets(msgBuffer, BUFFER_LENGHT, stdin);
		
		if(strncmp(msgBuffer,"help", strlen("help")) == 0){
        	printf("I am going to open help file\n");
        }

		else if(strncmp(msgBuffer,"exit", strlen("exit")) == 0){
			send(clientSocket, msgBuffer, strlen(msgBuffer), 0);
			return;
		}

		else if(strncmp(msgBuffer,"command", strlen("command")) == 0){
			send(clientSocket, msgBuffer, strlen(msgBuffer), 0);
			recv(clientSocket, rcvBuffer, BUFFER_LENGHT, 0);
		}
		memset(rcvBuffer, '\0', sizeof(char)*BUFFER_LENGHT);
	}
	printf("[+]Closing the connection.\n");
	shutdown(clientSocket, SHUT_RDWR);
}

