#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")
//change the following server_IP to which remoted server you want to connect,ex: the IP of google
char server_IP[] = "";
int main(int argc , char *argv[])
{	
	//Initialising winsock
	WSADATA wsa;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket
	SOCKET s;
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");
	
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(server_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );
	
	
	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected");
	
	//Send some data
	char *str = (char *)malloc(sizeof(char)*100);
	if(NULL == str){
		printf("malloc failure");
		exit(1);
	}
	scanf("%s",str);
	if(send(s,str,strlen(str),0) < 0){
		puts("send failed");
		return 1;
	}
	free(str);
	puts("Data Send\n");
	puts("take the server terminal a look");
	
	system("PAUSE");
	return 0;
}
