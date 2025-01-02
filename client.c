#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080

int socketFD;
void* readServer(void* arg)
{
	char* buffer[1024];
	while(1)
	{	
		memset(buffer,0,1024);
		read(socketFD,buffer, 1024);
		printf("%s",buffer);	
	}
	return NULL;
}
int main()
{
  struct sockaddr_in serveraddress;
  char buffer[1024] = {0};
	
//creating socket
 	socketFD = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == socketFD )
	{
		printf("Couln't create client side socket\n");
		return -1;
	}
//giving client address
	serveraddress.sin_family = AF_INET;
  serveraddress.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &serveraddress.sin_addr);
//connecting client to server
	if(connect(socketFD, (struct sockaddr *)&serveraddress, sizeof(serveraddress)) < 0) {
    	printf("Couldn't connect to the server\n");
			return 0;
    }	
	char user[100];
	printf("Connected to server(type exit to terminate).\nEnter Username:");fgets(user,100,stdin);
	user[strlen(user)-1] = '\0';
	send(socketFD,user,strlen(user),0);
//Send data to server
	pthread_t id;
	pthread_create(&id,0,readServer,NULL);
	
	while(1)
	{
		memset(buffer,0,1024);
		fgets(buffer,1024,stdin);
		send(socketFD,buffer,strlen(buffer),0);
 		if(strcmp(buffer, "exit\n") == 0)
    		break;
	}
	pthread_cancel(id);	
	close(socketFD);	
	return 0;
}
