#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")
/*
*===================================*
*	Tasks of server:                *
*                                   *
*	0.initialize winsock2           *
*	1.Open a SOCKET                 *
*	2.Bind to SOCKET                *
*	3.Listen to incoming connection *
*	4.Accept the connection         *
*	5.read/write                    *
*   6.Close SOCKET                  *
*===================================*
*/
//change the string of server_IP to your server IP
char server_IP[] = "";


int main(int argc,char* argv[]){
	//initialize winsock2
	WSADATA wsa;
	
	puts("\nInitialising Winsock...");
	
	if(WSAStartup(MAKEWORD(2,2),&wsa) != 0){
		printf("Failed. Error code : %d",WSAGetLastError());
		return 1;
	}
	puts("Initialised.\n");
	
	//1.Open a SOCKET
	SOCKET s;
	if((s = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET){
		printf("Could't create socket: %d",WSAGetLastError());
	}
	printf("SOCKET created.\n");
	
	//2.Bind to SOCKET
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(server_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	
	if(bind(s,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR){
		printf("Bind failed with error code: %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done\n");
	
	//3.Listen
	listen(s,3);
	puts("Waiting for incoming connections...\n");
	
	//4.Accept connections
	int c = 0;
	SOCKET new_socket;
	struct sockaddr_in client;
	c = sizeof(struct sockaddr_in);
	
	if((new_socket = accept(s,(struct sockaddr*)&client,&c)) == INVALID_SOCKET){
		printf("accept failed with error code : %d",WSAGetLastError());
		return 1;
	}
	puts("Connection accepted");
	//5.read
		char buf[1024];
		int recv_size = 0;
		if(recv_size = recv(new_socket,buf,1024,0) == SOCKET_ERROR){
			puts("recv failed");
		}
		puts("Data received\n");
		puts(buf);
	
	//Close SOCKET, release Winsock2
	closesocket(s);
	WSACleanup();
	system("PAUSE");
	return 0;
}
















