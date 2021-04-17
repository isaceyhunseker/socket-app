#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 2323
#define BUFFER_LENGHT 100

void main(){
    time_t result = time(NULL);
    printf("The current time is %s",  asctime(localtime(&result)));

	int sockfd;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;
	char buffer[BUFFER_LENGHT], msgBuffer[BUFFER_LENGHT] ="sea";
	char *cmd_type, *cmd_input, *username=NULL, *dest_user=NULL;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printf("[!]Server Socket Not Created");
		exit(-1);
	}
	printf("[+]Server Socket Created Sucessfully.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to Port number %d.\n", 2323);

	if((listen(sockfd, 5)) == -1){
		printf("[!]Listen Not Started");
		exit(-1);
	}
	printf("[+]Listening...\n");
    memset(buffer, '\0', sizeof(char)*BUFFER_LENGHT);
	memset(msgBuffer, '\0', sizeof(char)*BUFFER_LENGHT);

	while(newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size)){
		while ((recv(newSocket, buffer, BUFFER_LENGHT, 0)>0)) {
			printf("Message Received: %s", buffer);

			if(strncmp(buffer,"exit", strlen("exit")) == 0){
				return;
			}

			if(strncmp(buffer,"command", strlen("command")) == 0){
				strtok(buffer, ",");//nonused just eliminate in parsing
				cmd_type = strtok(NULL, ",");
				cmd_input = strtok(NULL, ",");

				if(strncmp(cmd_type,"datetime", strlen("datetime")) == 0)
					strcpy(msgBuffer, asctime(localtime(&result)));


				else if(strncmp(cmd_type,"login", strlen("login")) == 0){
					username = cmd_input;
					strcat(msgBuffer, "[+]The user has login: ");
					strcat(msgBuffer, username);
                	
				}

				else if(strncmp(cmd_type,"begin", strlen("begin")) == 0){
					if(!username){
						strcat(msgBuffer, "[!]Login before chat");
                	    send(newSocket, msgBuffer, strlen(msgBuffer), 0);
						break;
					}
					dest_user = cmd_input;
					strcat(msgBuffer, "[+]The user ");
					strcat(msgBuffer, username);
					strcat(msgBuffer, "begin the chat with ");
					strcat(msgBuffer, dest_user);
                	
				}

				else if(strncmp(cmd_type,"end", strlen("end")) == 0){
					if(!username || !dest_user){
						strcat(msgBuffer, "[!]There is no chat between these users");
                	    send(newSocket, msgBuffer, strlen(msgBuffer), 0);
						break;
					}
					dest_user = cmd_input;
					strcat(msgBuffer, "[+]The chat between ");
					strcat(msgBuffer, username);
					strcat(msgBuffer, "and");
					strcat(msgBuffer, dest_user);
					strcat(msgBuffer, "ended");
                	
				}
				else{
					printf("[!]Invalid second param");
					return;
				}
				send(newSocket, msgBuffer, strlen(msgBuffer), 0);
				memset(buffer, '\0', sizeof(char)*BUFFER_LENGHT);
				memset(msgBuffer, '\0', sizeof(char)*BUFFER_LENGHT);}
			}
		printf("[+]Closing the connection.\n");
		shutdown(newSocket, SHUT_RDWR);
		exit(0);
	}
}
