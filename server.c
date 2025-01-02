#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<pthread.h>

#define PORT 8080

struct client{
	int FD;
	struct sockaddr_in address;
	char name[100];	
};
struct client client[10];int count = 0;

void sendAll(char *buffer,int x) 
{
		char* buffer2 = calloc(1024,1);
		strcpy(buffer2,client[x].name);
		buffer2[strlen(buffer2)] = '>';
		strcpy(buffer2+strlen(buffer2),buffer);
    for(int i = 0 ; i<count ; i++)
        if(i!=x)
        {
            send(client[i].FD,buffer2, strlen(buffer2),0);
        }
}

void* recvNprint(void* id)
{	
	int i = *((int*)id);
	char* buffer = calloc(1024, sizeof(char));
	recv(client[i].FD, client[i].name,100,0);
	while(1)
	{
		memset(buffer,0,1024);
		recv(client[i].FD, buffer,1024,0);
		printf("%s>%s",client[i].name,buffer);
		if(strcmp(buffer,"exit\n")==0)
			break;
		sendAll(buffer,i);
	}

	close(client[i].FD);
	return NULL;
}

void createThread(int* clientFD)
{
	pthread_t id;
	pthread_create(&id,NULL,recvNprint,(void*)(clientFD));
}

void AcceptClient(int serverFD)
{
	int id[10] = {0,1,2,3,4,5,6,7,8,9};
	int addrlen = sizeof(client[0].address);
	while(1)
	{	
		int clientFD;
		client[count].FD = accept(serverFD,(struct sockaddr*)&client[count].address,(socklen_t *)&addrlen);
		if(client[count].FD == -1)
		{
			printf("\nCouldn't accept a client connection\n\n");
			continue;
		}
		else
		{
			createThread(id+count);
			count++;
		}
	}
}
void* terminate(void* arg)
{
	char store[10];
	while(1)
	{
		scanf("%s",store);
		if(strcmp(store,"close")==0)
			exit(0);
	}
	return NULL;
}
int main()
{
	struct sockaddr_in address;
	//Create socket
	int serverFD = socket(AF_INET,SOCK_STREAM,0);
	if(serverFD == -1 )
	{
		printf("Couldn't create socket\n");
		return -1;
	}
	//Bind the socket to address struct 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
	if(0!=bind(serverFD,(struct sockaddr*)&address,sizeof(address)))
	{
		printf("Couldn't bind the socket\n");
		close(serverFD);
		return -1;
	}	
	// Listen to client connections
	if(listen(serverFD,3)!=0)
	{
		printf("Couldn't listen to the client request\n");
		close(serverFD);
		return -1;
	}
	pthread_t id;
	printf("Server is listening to client request on port:%d\n",PORT);
	pthread_create(&id,NULL,terminate,NULL);
	//Accepticonnections
	//Recieve data

	AcceptClient(serverFD);
	close(serverFD);
	return 0;
}
