#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library


int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s,clean;
	struct sockaddr_in server;
	//Initialize winsock2
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");
	
	//indicate to server
	server.sin_addr.s_addr = inet_addr("192.168.1.104");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );
	
	char *str;
	while(1){
		//connect to server
		if(connect(s,(struct sockaddr*)&server,sizeof(server)) < 0){
			puts("connect error");
			return 1;
		}
		puts("Connected");
		str = (char *)malloc(sizeof(char)*100);
		if(NULL == str){
			printf("malloc failure");
			exit(1);
		}
		
		//send data
		scanf("%s",str);
		if(send(s,str,strlen(str),0) <0){
			puts("send failed");
			return 1;
		}
		printf("data send\n");
		free(str);
		
		//Re-create a socket
		s = clean;
		if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
		{
			printf("Could not create socket : %d" , WSAGetLastError());
		}
		printf("Socket created.\n");
	}
	system("PAUSE");
	return 0;
}

