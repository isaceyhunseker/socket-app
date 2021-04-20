#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 2323
#define BUFFER_LENGHT 100

void main()
{
	time_t result = time(NULL);
	printf("The current time is %s", asctime(localtime(&result)));

	int sockfd;
	struct sockaddr_in serverAddr;

    fd_set readfds;
    FD_ZERO(&readfds);

	int newSocket, clientSocket[2],c2Socket;
	struct sockaddr_in newAddr, c1Addr, c2Addr;

	socklen_t addr_size;
	char buffer[BUFFER_LENGHT], msgBuffer[BUFFER_LENGHT], 
        c1buffer[BUFFER_LENGHT], c2buffer[BUFFER_LENGHT];
	char *cmd_type, *cmd_input, *username = NULL, *dest_user = NULL;

    memset(buffer, '\0', sizeof(char) * BUFFER_LENGHT);
	memset(msgBuffer, '\0', sizeof(char) * BUFFER_LENGHT);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("[!]Server Socket Not Created");
		exit(-1);
	}
	printf("[+]Server Socket Created Sucessfully.\n");
   
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to Port number %d.\n", 2323);

	if ((listen(sockfd, 5)) == -1)
	{
		printf("[!]Listen Not Started");
		exit(-1);
	}
	printf("[+]Listening...\n");

   
   FD_SET(sockfd, &readfds);

	while(1)
	{
       
        int clntCnt = select(0 , &readfds , NULL , NULL , NULL);
    

        for (int i = 0; i<clntCnt; i++){
        clientSocket[clntCnt] = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
		FD_SET(clientSocket[clntCnt], &readfds);
         }

		if (recv(clientSocket[0], c1buffer, BUFFER_LENGHT, 0) > 0)
		{
			printf("from c1 %s", c1buffer);
		}

        if (recv(clientSocket[1], c2buffer, BUFFER_LENGHT, 0) > 0)
		{
			printf("from c2 %s", c2buffer);
		}
		printf("[+]Closing the connection.\n");
		exit(0);
	}
}
/*
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

void main()
{
	time_t result = time(NULL);
	printf("The current time is %s", asctime(localtime(&result)));

	int sockfd;
	struct sockaddr_in serverAddr;

	int c1Socket,c2Socket;
	struct sockaddr_in c1Addr, c2Addr;

	socklen_t addr_size;
	char buffer[BUFFER_LENGHT], msgBuffer[BUFFER_LENGHT] = "sea", 
        c1buffer[BUFFER_LENGHT], c2buffer[BUFFER_LENGHT];
	char *cmd_type, *cmd_input, *username = NULL, *dest_user = NULL;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("[!]Server Socket Not Created");
		exit(-1);
	}
	printf("[+]Server Socket Created Sucessfully.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to Port number %d.\n", 2323);

	if ((listen(sockfd, 5)) == -1)
	{
		printf("[!]Listen Not Started");
		exit(-1);
	}
	printf("[+]Listening...\n");
	memset(buffer, '\0', sizeof(char) * BUFFER_LENGHT);
	memset(msgBuffer, '\0', sizeof(char) * BUFFER_LENGHT);

    c1Socket = accept(sockfd, (struct sockaddr *)&c1Addr, &addr_size);
    c2Socket = accept(sockfd, (struct sockaddr *)&c2Addr, &addr_size);
	while (1)
	{
		if (recv(c1Socket, c1buffer, BUFFER_LENGHT, 0) > 0)
		{
			printf("from c1 %s", c1buffer);
		}

        if (recv(c2Socket, c2buffer, BUFFER_LENGHT, 0) > 0)
		{
			printf("from c2 %s", c2buffer);
		}
		printf("[+]Closing the connection.\n");
		exit(0);
	}
}

*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 2323
#define BUFFER_LENGHT 100
#define TRUE 1
void main()
{
    int opt = TRUE;
    time_t result = time(NULL);
    printf("The current time is %s", asctime(localtime(&result)));

    int serverSocket, newSocket, clientSocket[2] = {0, 0}, maxClient = 2;
    struct sockaddr_in serverAddr;

    fd_set readfds;
    FD_ZERO(&readfds);

    int c1Socket, c2Socket;
    struct sockaddr_in c1Addr, c2Addr;

    socklen_t addr_size;
    char buffer[BUFFER_LENGHT], msgBuffer[BUFFER_LENGHT] = "sea";
    char *cmd_type, *cmd_input, *username = NULL, *dest_user = NULL;

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("[!]Server Socket Not Created");
        exit(-1);
    }
    printf("[+]Server Socket Created Sucessfully.\n");

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        printf("[!]setsockopt Failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    printf("[+]Bind to Port number %d.\n", 2323);

    if ((listen(serverSocket, 5)) == -1)
    {
        printf("[!]Listen Not Started");
        exit(-1);
    }
    printf("[+]Listening...\n");

    FD_SET(serverSocket, &readfds);
    memset(buffer, '\0', sizeof(char) * BUFFER_LENGHT);
    memset(msgBuffer, '\0', sizeof(char) * BUFFER_LENGHT);

    c1Socket = accept(serverSocket, (struct sockaddr *)&c1Addr, &addr_size);
    c2Socket = accept(serverSocket, (struct sockaddr *)&c2Addr, &addr_size);

    while (TRUE)
    {
        fd_set inMsg = readfds;
        int socketCount = select(0, &inMsg, NULL, NULL, NULL);
        for (int i = 0; i < socketCount; i++)
        {
            if (!FD_ISSET(socketCount, &inMsg))
                continue;
            
            new_socket = accept(master_socket, (struct sockaddr *)&inMsg, (socklen_t*)&addr_size)    
        }
    }
    printf("[+]Closing the connection.\n");
    shutdown(newSocket, SHUT_RDWR);
    exit(0);
}

*/
